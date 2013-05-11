#include "config/AuthConfig.h"
#include "network/AuthServer.h"

int main()
{
    AuthConfig authConfig;
    AuthServer authServer;

    authServer.start(authConfig.getPort(), authConfig.getMaxClients());

    return 0;
}
