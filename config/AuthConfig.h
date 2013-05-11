#ifndef AUTH_CONFIG_H
#define AUTH_CONFIG_H

#include "ConfigManager.h"

class AuthConfig
{
    public:
        AuthConfig();
        unsigned short getPort();
        unsigned short getMaxClients();

    private:
        unsigned short port;
        unsigned short maxClients;
};

#endif // AUTH_CONFIG_H
