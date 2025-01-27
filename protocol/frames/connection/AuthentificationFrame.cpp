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

    switch(message->getMessageId())
    {
    case 4:
        processMessage((IdentificationMessage*)message, client);
        state = true;
        break;

    case 40:
        processMessage((ServerSelectionMessage*)message, client);
        state = true;
        break;

    case 888:
        processMessage((ClearIdentificationMessage*)message, client);
        state = true;
        break;
    }

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
    NetworkManager::sendTo(client->socket, rdm.getInstance());
}

void AuthentificationFrame::processMessage(ClearIdentificationMessage* message, Client* client)
{
    bool failAuth = true;
    int reason = UNKNOWN_AUTH_ERROR;

    Database* database = Database::Instance();

    try
    {
        mysqlpp::Query queryUser = database->db->query("SELECT *, UNIX_TIMESTAMP(subscriptionEndDate) as subEndDate, UNIX_TIMESTAMP(accountCreation) as accCreation FROM accounts WHERE login = %0q AND password = %1q");
        queryUser.parse();
        mysqlpp::StoreQueryResult resUser = queryUser.store(message->user, message->password);

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
                ism.initIdentificationSuccessMessage(login, nickname, accountId, 0, hasRights, "Question ?", hasRights ? 0 : subscriptionEndDate*1000, false, accountCreation*1000);
                NetworkManager::sendTo(client->socket, ism.getInstance());

                try
                {
                    vector<GameServerInformations*> servers;

                    mysqlpp::Query queryServersList = database->db->query("SELECT * FROM game_servers");
                    mysqlpp::StoreQueryResult resServersList = queryServersList.store();

                    for(size_t i = 0; i < resServersList.num_rows(); ++i)
                    {
                        int serverId = resServersList[i]["id"];
                        int type = resServersList[i]["type"];
                        const char* serverDB = resServersList[i]["database"];
                        int status = resServersList[i]["status"];

                        try
                        {
                            database->db->select_db(serverDB);

                            mysqlpp::Query queryCountCharacters = database->db->query("SELECT COUNT(*) as count FROM characters WHERE accountId = %0");
                            queryCountCharacters.parse();
                            mysqlpp::StoreQueryResult resCountCharacters = queryCountCharacters.store(accountId);

                            int count = resCountCharacters[0]["count"];

                            if(type > 0 && !hasRights)
                                status = NOJOIN;

                            GameServerInformations* gsi = new GameServerInformations();
                            gsi->initGameServerInformations(serverId, status, 0, true, count, 0);
                            servers.push_back(gsi);
                        }
                        catch(const mysqlpp::Exception& e)
                        {
                            Logger::Log(ERROR, sLog(), e.what());
                        }
                    }

                    database->selectDefault();

                    ServersListMessage slm;
                    slm.initServersListMessage(servers);
                    NetworkManager::sendTo(client->socket, slm.getInstance());

                    try
                    {
                        client->accountId = accountId;
                        client->token = genToken(10);

                        mysqlpp::Query queryStockToken = database->db->query("UPDATE accounts SET token = %1q WHERE id = %0");
                        queryStockToken.parse();
                        mysqlpp::SimpleResult resStockToken = queryStockToken.execute(client->accountId, client->token);
                    }
                    catch(const mysqlpp::Exception& e)
                    {
                        Logger::Log(ERROR, sLog(), e.what());
                    }
                }
                catch(const mysqlpp::Exception& e)
                {
                    Logger::Log(ERROR, sLog(), e.what());
                }
            }
        }
        else
            reason = WRONG_CREDENTIALS;
    }
    catch(const mysqlpp::Exception& e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }

    if(failAuth)
    {
        IdentificationFailedMessage ifm;
        ifm.initIdentificationFailedMessage(reason);
        NetworkManager::sendTo(client->socket, ifm.getInstance());
    }
}

void AuthentificationFrame::processMessage(ServerSelectionMessage* message, Client* client)
{
    Database* database = Database::Instance();

    try
    {
        mysqlpp::Query querySelectedServer = database->db->query("SELECT * FROM game_servers WHERE id = %0");
        querySelectedServer.parse();
        mysqlpp::StoreQueryResult resSelectedServer = querySelectedServer.store(message->serverId);

        if(!resSelectedServer.empty())
        {
            const char* serverIP = resSelectedServer[0]["ip"];
            unsigned short serverPort = resSelectedServer[0]["port"];

            SelectedServerDataMessage ssdm;
            ssdm.initSelectedServerDataMessage(message->serverId, (char*)serverIP, serverPort, true, client->token);
            NetworkManager::sendTo(client->socket, ssdm.getInstance());

            shutdown(client->socket, 2);
        }
        else
        {
            SelectedServerRefusedMessage ssrm;
            ssrm.initSelectedServerRefusedMessage(message->serverId, SERVER_CONNECTION_ERROR_NO_REASON, STATUS_UNKNOWN);
            NetworkManager::sendTo(client->socket, ssrm.getInstance());
        }
    }
    catch(const mysqlpp::Exception& e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }
}
