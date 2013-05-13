#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include <cstring>

#include "../../common/Logger.h"
#include "NetworkManager.h"

using namespace std;

class AuthServer : public NetworkManager
{
    public:
        AuthServer();

    private:
        void onClientConnected(SOCKET ClientSocket);
        void onClientDisconnected(Client client, int number);
        void onDataReceive(Client client, char *buffer, int bufferSize);
};

#endif // AUTH_SERVER_H
