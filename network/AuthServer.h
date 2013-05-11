#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include <iostream>
#include "NetworkManager.h"

using namespace std;

class AuthServer : public NetworkManager
{
    public:
        AuthServer();

    private:
        void onNewClient();
        void onCloseClient();
        void onDataReceive();
};

#endif // AUTH_SERVER_H
