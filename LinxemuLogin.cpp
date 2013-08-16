#include <iostream>

#include "config/ConfigLogin.h"
#include "database/Database.h"
#include "worker/Worker.h"
#include "network/LoginServer.h"

using namespace std;

int main()
{
    cout << "Linxemu LOGIN (DEV) by Sorrow (" << __DATE__ << " " << __TIME__ << ")" << endl << endl;

    Config* config = Config::Instance();
    config->init("login.ini");

    Database* database = Database::Instance();
    database->init();

    LoginServer loginServer;
    Worker worker;

    loginServer.start();

    return 42;
}
