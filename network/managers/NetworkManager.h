#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>

#include "../../utils/utils.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define PACKET_MAX_SIZE 1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

using namespace std;

enum State { NEW_PACKET, HEADER_OK, LENGTH_OK };

typedef struct Client
{
    SOCKET sock;
    State phase;
    queue<char> bufferQueue;
    unsigned short lastMessageId;
    unsigned short lastMessageLengthType;
    unsigned short lastMessageLength;
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
        //void PacketParser(Client client, char *buffer, int bufferSize);
        void PacketParser(Client client);
        unsigned short getMessageId(unsigned short firstOctet);
        unsigned short getMessageLengthType(unsigned short firstOctet);
        unsigned short readMessageLength(unsigned short byteLenDynamicHeader, MessageReader *packet);

    protected:
        virtual void onClientConnected(SOCKET ClientSocket) = 0;
        virtual void onClientDisconnected(Client client, int number) = 0;
        virtual void onDataReceive(Client client, Packet packet) = 0;

        string getClientIP(SOCKET ClientSocket);
        string getClientPort(SOCKET ClientSocket);

        void writePacket(MessageWriter *output, int msgId, char* data, unsigned int len);
        unsigned int computeTypeLen(unsigned int len);
        unsigned int subComputeStaticHeader(unsigned int msgId, unsigned int typeLen);

        Client *clients;
        int nbClients;
};

#endif // NETWORK_MANAGER_H
