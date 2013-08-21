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
            NetworkManager::sendTo(client->socket, atam.getInstance());

            ServerSettingsMessage ssm;
            ssm.initServerSettingsMessage("fr", 0, 0);
            NetworkManager::sendTo(client->socket, ssm.getInstance());

            AccountCapabilitiesMessage acm;
            acm.initAccountCapabilitiesMessage(client->accountId, false, 0x7FFF, 0x7FFF, 0); // 0x7FFF = 15 bits à 1 en binaire, représentant les 15 classes
            NetworkManager::sendTo(client->socket, acm.getInstance());
        }
        else
        {
            AuthenticationTicketRefusedMessage atrm;
            atrm.initAuthenticationTicketRefusedMessage();
            NetworkManager::sendTo(client->socket, atrm.getInstance());
        }
    }
    catch(const mysqlpp::Exception& e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }
}

void GameServerApproachFrame::processMessage(CharactersListRequestMessage* message, Client* client)
{
    Database* database = Database::Instance();
    vector<CharacterBaseInformations*> characters;

    try
    {
        mysqlpp::Query queryCharactersList = database->db->query("SELECT * FROM characters WHERE accountId = %0");
        queryCharactersList.parse();
        mysqlpp::StoreQueryResult resCharactersList = queryCharactersList.store(client->accountId);

        for(size_t i = 0; i < resCharactersList.num_rows(); ++i)
        {
            int characterId = resCharactersList[i]["id"];
            const char* _name = resCharactersList[i]["name"];
            int breed = resCharactersList[i]["class"];
            int sex = resCharactersList[i]["sex"];
            int level = resCharactersList[i]["level"];
            int skin = resCharactersList[i]["skin"];
            int cosmetic = resCharactersList[i]["cosmetic"];

            int color1 = resCharactersList[i]["color1"];
            int color2 = resCharactersList[i]["color2"];
            int color3 = resCharactersList[i]["color3"];
            int color4 = resCharactersList[i]["color4"];
            int color5 = resCharactersList[i]["color5"];

            EntityLook* entityLook = new EntityLook;
            vector<int> skins;
            vector<int> indexedColors;
            vector<int> scales;
            vector<SubEntity*> subentities;

            char* name = new char[strlen(_name)];
            strcpy(name, _name);

            skins.push_back(skin);
            skins.push_back(cosmetic);

            try
            {
                mysqlpp::Query queryCharactersItemsList = database->db->query("SELECT skinId FROM items WHERE characterId = %0 AND position IN (%1, %2, %3)");
                queryCharactersItemsList.parse();
                mysqlpp::StoreQueryResult resCharactersItemsList = queryCharactersItemsList.store(characterId, ACCESSORY_POSITION_HAT, ACCESSORY_POSITION_CAPE, ACCESSORY_POSITION_SHIELD);

                for(size_t j = 0; j < resCharactersItemsList.num_rows(); ++j)
                {
                    int skinId = resCharactersItemsList[j]["skinId"];
                    skins.push_back(skinId);
                }
            }
            catch(const mysqlpp::Exception& e)
            {
                Logger::Log(ERROR, sLog(), e.what());
            }

            indexedColors.push_back(color1 + 0x01000000);
            indexedColors.push_back(color2 + 0x02000000);
            indexedColors.push_back(color3 + 0x03000000);
            indexedColors.push_back(color4 + 0x04000000);
            indexedColors.push_back(color5 + 0x05000000);

            scales.push_back(160);

            entityLook->initEntityLook(1, skins, indexedColors, scales, subentities);

            CharacterBaseInformations* character = new CharacterBaseInformations;
            character->initCharacterBaseInformations(characterId, level, (char*)name, entityLook, breed, sex == 1 ? true : false);

            characters.push_back(character);
        }
    }
    catch(const mysqlpp::Exception& e)
    {
        Logger::Log(ERROR, sLog(), e.what());
    }

    CharactersListMessage clm;
    clm.initCharactersListMessage(false, characters);
    NetworkManager::sendTo(client->socket, clm.getInstance());
}
