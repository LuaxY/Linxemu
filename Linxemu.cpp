#include <iostream>

#include "config/AuthConfig.h"
#include "network/managers/AuthServer.h"

using namespace std;

void displayTitle();

int main()
{
    displayTitle();

    AuthConfig authConfig;
    AuthServer authServer;

    authServer.start(authConfig.getPort(), authConfig.getMaxClients());

    return 0;
}

void displayTitle()
{
    cout << "Linxemu (ALPHA) par Sorrow." << endl << endl;
}
