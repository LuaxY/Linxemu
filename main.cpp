#include "config/ConfigManager.h"
#include "network/AuthServer.h"

int main()
{
    ConfigManager config("config.cfg");

    short authPort = (short)config.getInt("authport");
    short maxClients = (short)config.getInt("maxclients");

    //AuthConfig authConfig;

    AuthServer authServer;
    authServer.start(authPort, maxClients); // port, max clients
    //authServer.start(authConfig.getPort(), authConfig.getMaxClients()); // port, max clients

    return 0;
}
