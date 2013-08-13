#include <iostream>

#include "config/Config.h"
#include "database/Database.h"
#include "worker/Worker.h"
#include "network/AuthServer.h"

using namespace std;

int main()
{
    cout << "Linxemu (DEV) by Sorrow (" << __DATE__ << " " << __TIME__ << ")" << endl << endl;

    Config* config = Config::Instance();
    config->init("config.ini");

    Database* database = Database::Instance();
    database->init();

    AuthServer authServer;
    Worker worker;

    authServer.start();

    return 42;
}
