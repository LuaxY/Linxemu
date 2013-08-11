#include "AuthentificationFrame.h"

IFrame* AuthentificationFrame::getInstance() const
{
    return new AuthentificationFrame(*this);
}

char* AuthentificationFrame::getFrameName()
{
	return "AuthentificationFrame";
}

bool AuthentificationFrame::process(INetworkMessage* message, Client* client)
{
    bool processState = false;
    MessageWriter *data = new MessageWriter();
    MessageWriter *packet = new MessageWriter();

    switch(message->getMessageId())
    {
        case 4: // IdentificationMessage
        {
            ifstream::pos_type size;
            char *newPacket;

            // Merci à Munrek pour le SWF
            ifstream packetSWF("DofusAuthentificator.swf", ios::in | ios::binary | ios::ate);
            if(packetSWF.is_open())
            {
                size = packetSWF.tellg();
                newPacket = new char[size];
                packetSWF.seekg(0, ios::beg);
                packetSWF.read(newPacket, size);
                packetSWF.close();
            }
            else
                Logger::Log(ERROR, sLog(), "Unable to open DofusAuthentificator.swf");

            RawDataMessage rdm;
            rdm.initRawDataMessage(newPacket, size);
            rdm.pack(data);

            NetworkManager::writePacket(packet, rdm.getMessageId(), data->getBuffer(), data->getPosition());
            NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), rdm.getInstance());

            processState = true;
            break;
        }

        case 182: // BasicPingMessage
        {
            BasicPongMessage bpm;
            bpm.initBasicPongMessage(true);
            bpm.pack(data);

            NetworkManager::writePacket(packet, bpm.getMessageId(), data->getBuffer(), data->getPosition());
            NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), bpm.getInstance());

            processState = true;
            break;
        }

        case 888: // ClearIdentificationMessage
        {
            ClearIdentificationMessage cim((ClearIdentificationMessage*)message);

            bool fail = true;
            int reason = 99;

            SQLite::Database db("lnx.db");
            SQLite::Statement query(db, "SELECT * FROM accounts WHERE login = ? AND password = ?");
            query.bind(1, cim.user);
            query.bind(2, cim.password);

            if(query.executeStep())
            {
                int accountId = query.getColumn(0);
                const char* login = query.getColumn(1);
                int rank = query.getColumn(3);
                int banned = query.getColumn(4);
                int reinitialized = query.getColumn(5);
                const char* nickname = query.getColumn(6);

                bool isBanned = banned > 0 ? true : false;
                bool isReinitialized = reinitialized > 0 ? true : false;
                bool hasRights = rank > 0 ? true : false;

                if(isBanned)
                    reason = BANNED;
                else if(isReinitialized)
                    reason = CREDENTIALS_RESET;
                else
                {
                    fail = false;

                    IdentificationSuccessMessage ism;
                    ism.initIdentificationSuccessMessage(login, nickname, accountId, 0, hasRights, "Question ?", 0, false, 0);
                    ism.pack(data);

                    NetworkManager::writePacket(packet, ism.getMessageId(), data->getBuffer(), data->getPosition());
                    NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), ism.getInstance());

                    data->reset();
                    packet->reset();

                    vector<GameServerInformations*> servers;
                    GameServerInformations* test = new GameServerInformations();
                    test->initGameServerInformations(900, NOJOIN, 0, true, 2, 0); // 900 = serveur test
                    servers.push_back(test);

                    ServersListMessage slm;
                    slm.initServersListMessage(servers);
                    slm.pack(data);

                    NetworkManager::writePacket(packet, slm.getMessageId(), data->getBuffer(), data->getPosition());
                    NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), slm.getInstance());

                    delete test;
                }
            }
            else
                reason = WRONG_CREDENTIALS;

            if(fail)
            {
                IdentificationFailedMessage ifm;
                ifm.initIdentificationFailedMessage(reason);
                ifm.pack(data);

                NetworkManager::writePacket(packet, ifm.getMessageId(), data->getBuffer(), data->getPosition());
                NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), ifm.getInstance());
            }

            processState = true;
            break;
        }
    }

    delete data;
    delete packet;

    return processState;
}
