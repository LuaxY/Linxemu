#include <iostream>

#include "config/ConfigGame.h"
#include "database/Database.h"
#include "worker/Worker.h"
#include "network/GameServer.h"

using namespace std;

int main()
{
    cout << "Linxemu GAME (DEV) by Sorrow (" << __DATE__ << " " << __TIME__ << ")" << endl << endl;

    Config* config = Config::Instance();
    config->init("game.ini");

    Database* database = Database::Instance();
    database->init();

    GameServer gameServer;
    Worker worker;

    gameServer.start();

    return 42;
}
