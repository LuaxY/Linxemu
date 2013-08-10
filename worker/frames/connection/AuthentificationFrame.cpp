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

            int reason = 99;

            SQLite::Database db("lnx.db");
            SQLite::Statement query(db, "SELECT * FROM accounts WHERE login = ? AND password = ?");
            query.bind(1, cim.user);
            query.bind(2, cim.password);

            if(query.executeStep())
            {
                Logger::Log(WORKER, sLog(), "User '", false);
                cout << query.getColumn(1) << "' is now logged" << endl;
                reason = 5; // All server in maintenance
            }
            else
            {
                Logger::Log(ERROR, sLog(), "Bad login/password");
                reason = 2; // Bad login/password
            }

            IdentificationFailedMessage ifm;
            ifm.initIdentificationFailedMessage(reason);
            ifm.pack(data);

            NetworkManager::writePacket(packet, ifm.getMessageId(), data->getBuffer(), data->getPosition());
            NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), ifm.getInstance());

            processState = true;
            break;
        }
    }

    delete data;
    delete packet;

    return processState;
}
