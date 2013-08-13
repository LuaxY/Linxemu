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
    bool state = false;

    data = new MessageWriter();
    packet = new MessageWriter();

    switch(message->getMessageId())
    {
        case 4:
            processMessage((IdentificationMessage*)message, client);
            state = true;
            break;

        case 182:
            processMessage((BasicPingMessage*)message, client);
            state = true;
            break;

        case 888:
            processMessage((ClearIdentificationMessage*)message, client);
            state = true;
            break;
    }

    delete data;
    delete packet;

    return state;
}

void AuthentificationFrame::processMessage(IdentificationMessage* message, Client* client)
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
}

void AuthentificationFrame::processMessage(BasicPingMessage* message, Client* client)
{
    BasicPongMessage bpm;
    bpm.initBasicPongMessage(true);
    bpm.pack(data);

    NetworkManager::writePacket(packet, bpm.getMessageId(), data->getBuffer(), data->getPosition());
    NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), bpm.getInstance());
}

void AuthentificationFrame::processMessage(ClearIdentificationMessage* message, Client* client)
{
    ClearIdentificationMessage cim((ClearIdentificationMessage*)message);

    bool failAuth = true;
    int reason = UNKNOWN_AUTH_ERROR;

    Database* database = Database::Instance();

    try
    {
        mysqlpp::Query queryUser = database->db->query("SELECT *, UNIX_TIMESTAMP(subscriptionEndDate) as subEndDate, UNIX_TIMESTAMP(accountCreation) as accCreation FROM accounts WHERE login = %0q AND password = %1q");
        queryUser.parse();
        mysqlpp::StoreQueryResult resUser = queryUser.store(cim.user, cim.password);

        if(!resUser.empty())
        {
            int accountId = resUser[0]["id"];
            const char* login = resUser[0]["login"];
            int rank = resUser[0]["rank"];
            int banned = resUser[0]["banned"];
            int reinitialized = resUser[0]["reinitialized"];
            const char* nickname = resUser[0]["nickname"];
            double subscriptionEndDate = resUser[0]["subEndDate"];
            double accountCreation = resUser[0]["accCreation"];

            bool isBanned = banned > 0 ? true : false;
            bool isReinitialized = reinitialized > 0 ? true : false;
            bool hasRights = rank > 0 ? true : false;

            if(isBanned)
                reason = BANNED;
            else if(isReinitialized)
                reason = CREDENTIALS_RESET;
            else
            {
                failAuth = false;

                IdentificationSuccessMessage ism;
                ism.initIdentificationSuccessMessage(login, nickname, accountId, 0, hasRights, "Question ?", subscriptionEndDate*1000, false, accountCreation*1000);
                ism.pack(data);

                NetworkManager::writePacket(packet, ism.getMessageId(), data->getBuffer(), data->getPosition());
                NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), ism.getInstance());

                data->reset();
                packet->reset();

                try
                {
                    vector<GameServerInformations*> servers;

                    mysqlpp::Query queryServersList = database->db->query("SELECT * FROM game_servers");
                    mysqlpp::StoreQueryResult resServersList = queryServersList.store();

                    for(size_t i = 0; i < resServersList.num_rows(); ++i)
                    {
                        int serverId = resServersList[i]["id"];
                        int type = resServersList[i]["type"];
                        int state = ONLINE;

                        if(type > 0 && !hasRights)
                            state = NOJOIN;

                        GameServerInformations* gsi= new GameServerInformations();
                        gsi->initGameServerInformations(serverId, state, 0, true, 1, 0);
                        servers.push_back(gsi);
                    }

                    ServersListMessage slm;
                    slm.initServersListMessage(servers);
                    slm.pack(data);

                    NetworkManager::writePacket(packet, slm.getMessageId(), data->getBuffer(), data->getPosition());
                    NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), slm.getInstance());
                }
                catch(const mysqlpp::BadQuery &e)
                {
                    Logger::Log(ERROR, sLog(), e.what());
                }
            }
        }
        else
            reason = WRONG_CREDENTIALS;
    }
    catch(const mysqlpp::BadQuery &e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }

    if(failAuth)
    {
        IdentificationFailedMessage ifm;
        ifm.initIdentificationFailedMessage(reason);
        ifm.pack(data);

        NetworkManager::writePacket(packet, ifm.getMessageId(), data->getBuffer(), data->getPosition());
        NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), ifm.getInstance());
    }
}
