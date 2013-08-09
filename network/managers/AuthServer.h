#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include <cstring>

#include "../../utils/utils.h"
#include "NetworkManager.h"
#include "MessageReceiver.h"
#include "../../worker/managers/Worker.h"

using namespace std;

class AuthServer : public NetworkManager
{
    public:
        AuthServer();

    private:
        void onClientConnected(SOCKET ClientSocket);
        void onClientDisconnected(Client client, int number);
        void onDataReceive(Client client, Packet* packet);
};

#endif // AUTH_SERVER_H
