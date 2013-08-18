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
    vector<CharacterBaseInformations*> characters;

    /** LOOP **/
    EntityLook* entityLook = new EntityLook;
    vector<int> skins;
    vector<int> indexedColors;
    vector<int> scales;
    vector<SubEntity*> subentities;

    skins.push_back(1664);
    skins.push_back(2246);
    skins.push_back(460);
    skins.push_back(461);
    skins.push_back(462);
    skins.push_back(1250);

    indexedColors.push_back(0x01fed192);
    indexedColors.push_back(0x02fbf1bf);
    indexedColors.push_back(0x0334271a);
    indexedColors.push_back(0x04f9e79f);
    indexedColors.push_back(0x05ab8a50);

    scales.push_back(160);

    entityLook->initEntityLook(1, skins, indexedColors, scales, subentities);

    CharacterBaseInformations* player1 = new CharacterBaseInformations;
    player1->initCharacterBaseInformations(1, 50, "Yena", entityLook, 0, true);

    characters.push_back(player1);
    /** END LOOP **/

    CharactersListMessage clm;
    clm.initCharactersListMessage(false, characters);
    clm.pack(data);

    NetworkManager::writePacket(packet, clm.getMessageId(), data->getBuffer(), data->getPosition());
    NetworkManager::sendTo(client->socket, packet->getBuffer(), packet->getPosition(), clm.getInstance());
}
