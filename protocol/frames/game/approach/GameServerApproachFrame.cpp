#include "GameServerApproachFrame.h"

IFrame* GameServerApproachFrame::getInstance() const
{
    return new GameServerApproachFrame(*this);
}

char* GameServerApproachFrame::getFrameName()
{
    return "GameServerApproachFrame";
}

bool GameServerApproachFrame::process(INetworkMessage* message, Client* client)
{
    bool state = false;

    data = new MessageWriter();
    packet = new MessageWriter();

    switch(message->getMessageId())
    {
    case 110:
        processMessage((AuthenticationTicketMessage*)message, client);
        state = true;
        break;

    case 150:
        processMessage((CharactersListRequestMessage*)message, client);
        state = true;
        break;
    }

    delete data;
    delete packet;

    return state;
}

void GameServerApproachFrame::processMessage(AuthenticationTicketMessage* message, Client* client)
{
    Database* database = Database::Instance();
    Config* config = Config::Instance();

    try
    {
        database->db->select_db(config->login_db);

        mysqlpp::Query queryUser = database->db->query("SELECT id FROM accounts WHERE token = %0q");
        queryUser.parse();
        mysqlpp::StoreQueryResult resUser = queryUser.store(message->ticket);

        database->selectDefault();

        if(!resUser.empty())
        {
            client->accountId = resUser[0]["id"];

            AuthenticationTicketAcceptedMessage atam;
            atam.initAuthenticationTicketAcceptedMessage();
            atam.pack(data);

            NetworkManager::writePacket(packet, atam.getMessageId(), data->getBuffer(), data->getPosition());
            NetworkManager::sendTo(client->socket, packet->getBuffer(), packet->getPosition(), atam.getInstance());
        }
        else
        {
            AuthenticationTicketRefusedMessage atrm;
            atrm.initAuthenticationTicketRefusedMessage();
            atrm.pack(data);

            NetworkManager::writePacket(packet, atrm.getMessageId(), data->getBuffer(), data->getPosition());
            NetworkManager::sendTo(client->socket, packet->getBuffer(), packet->getPosition(), atrm.getInstance());
        }
    }
    catch(const mysqlpp::Exception& e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }
}

void GameServerApproachFrame::processMessage(CharactersListRequestMessage* message, Client* client)
{
    cout << "Tas des personnages ?" << endl;
}
