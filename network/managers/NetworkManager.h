#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
//#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <iostream>

#include "../../utils/utils.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

using namespace std;

typedef struct Client
{
   SOCKET sock;
};

typedef struct Packet
{
    unsigned short messageId;
    unsigned short messageLength;
    char* buffer;
};

class NetworkManager
{
    public:
        NetworkManager();
        ~NetworkManager();
        void start(unsigned short port, unsigned short maxClients);

    private:
        void PacketParser(Client client, char *buffer, int bufferSize);
        unsigned short getMessageId(unsigned short firstOctet);
        unsigned short readMessageLength(unsigned short staticHeader, MessageReader *packet);

    protected:
        virtual void onClientConnected(SOCKET ClientSocket) = 0;
        virtual void onClientDisconnected(Client client, int number) = 0;
        virtual void onDataReceive(Client client, Packet packet) = 0;

        string getClientIP(SOCKET ClientSocket);

        Client *clients;
        int nbClients;
};

#endif // NETWORK_MANAGER_H
