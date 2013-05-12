#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include <cstring>

#include "NetworkManager.h"

using namespace std;

class AuthServer : public NetworkManager
{
    public:
        AuthServer();

    private:
        void onNewClient(SOCKET ClientSocket);
        void onCloseClient(Client client, int number);
        void onDataReceive(Client client, char *buffer, int sizeBuffer);
};

#endif // AUTH_SERVER_H
