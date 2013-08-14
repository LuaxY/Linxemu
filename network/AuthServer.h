#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include <cstring>

#include "../utils/utils.h"
#include "NetworkManager.h"
#include "MessageReceiver.h"
#include "../worker/Worker.h"

using namespace std;

class AuthServer : public NetworkManager
{
    public:
        AuthServer();

    private:
        void onClientConnected(SOCKET ClientSocket);
        void onClientDisconnected(Client* client, int i);
        void onDataReceive(Client* client, Packet* packet);

        unsigned int requiredVersion;
        unsigned int currentVersion;
        char *salt;
        char *key;
        ifstream::pos_type keySize;
};

#endif // AUTH_SERVER_H
