#include "AuthConfig.h"

AuthConfig::AuthConfig()
{
    ConfigManager config("auth.cfg");

    port = (short)config.getInt("authport");
    maxClients = (short)config.getInt("maxclients");
}

unsigned short AuthConfig::getPort()
{
    return port;
}

unsigned short AuthConfig::getMaxClients()
{
    return maxClients;
}
