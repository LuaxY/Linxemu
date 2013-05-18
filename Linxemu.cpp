#include <iostream>

#include "config/AuthConfig.h"
#include "frames/Worker.h"
#include "network/managers/AuthServer.h"

using namespace std;

int main()
{
    cout << "Linxemu (DEV) by Sorrow." << endl << endl;

    AuthConfig authConfig;
    AuthServer authServer;
    Worker worker;

    authServer.start(authConfig.getPort(), authConfig.getMaxClients());

    return 0;
}
