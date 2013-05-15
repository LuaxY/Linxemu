#include <iostream>

#include "config/AuthConfig.h"
#include "network/messages/Worker.h"
#include "network/managers/AuthServer.h"

using namespace std;

void displayTitle();

int main()
{
    displayTitle();

    AuthConfig authConfig;
    AuthServer authServer;
    //Worker worker;

    //worker.run();

    authServer.start(authConfig.getPort(), authConfig.getMaxClients());

    return 0;
}

void displayTitle()
{
    cout << "Linxemu (DEV) par Sorrow." << endl << endl;
}
