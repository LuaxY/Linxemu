#include <iostream>

#include "config/AuthConfig.h"
#include "worker/Worker.h"
#include "network/AuthServer.h"

using namespace std;

int main()
{
    cout << "Linxemu (DEV) by Sorrow (" << __DATE__ << " " << __TIME__ << ")" << endl << endl;

    AuthConfig* authConfig = AuthConfig::Instance();
    authConfig->init("config.ini");

    AuthServer authServer;
    Worker worker;

    authServer.start();

    return 42;
}
