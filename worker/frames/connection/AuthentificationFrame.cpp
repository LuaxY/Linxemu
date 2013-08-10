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

            /** Temporaire **/
            sqlite3 *db;
            sqlite3_stmt *res;
            int sqlReturn = 0, reason = 99;

            sqlReturn = sqlite3_open("lnx.db", &db);

            if(sqlReturn)
                Logger::Log(ERROR, sLog(), "Can't open SQLite Database");

            char query[1000];
            strcpy(query, "SELECT * FROM accounts WHERE login = '");
            strcat(query, cim.user);
            strcat(query, "' AND password = '");
            strcat(query, cim.password);
            strcat(query, "';");

            sqlReturn = sqlite3_prepare_v2(db, query, -1, &res, 0);

            if(sqlReturn != SQLITE_OK)
            {
                Logger::Log(ERROR, sLog(), "SQLite error: ", false);
                cout << sqlReturn << endl;
            }

            if(sqlite3_step(res) == SQLITE_ROW)
            {
                Logger::Log(WORKER, sLog(), "User '", false);
                cout << sqlite3_column_text(res, 1) << "' is now logged" << endl;

                reason = 5; // All server in maintenance
            }
            else
            {
                Logger::Log(ERROR, sLog(), "Bad login/password");
                reason = 2; // Bad login/password
            }

            sqlite3_finalize(res);
            sqlite3_close(db);
            /****************/

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
