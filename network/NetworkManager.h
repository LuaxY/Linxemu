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
#include <vector>

#include "../utils/utils.h"
#include "../protocol/messages/INetworkMessage.h"
#ifdef GAME
#include "../config/ConfigGame.h"
#else
#include "../config/ConfigLogin.h"
#endif
#include "../common/Client.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define PACKET_MAX_SIZE 1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

using namespace std;

/*typedef struct Client
{
    SOCKET sock;
    State phase;
    queue<char> bufferQueue;
    unsigned short lastMessageId;
    unsigned short lastMessageLengthType;
    unsigned short lastMessageLength;
};*/

typedef struct Packet
{
    unsigned short messageId;
    unsigned short messageLength;
    char* buffer;
};

class NetworkManager
{
    public:
        NetworkManager(){};
        ~NetworkManager(){};
        void start();

        static string getClientIP(SOCKET ClientSocket);
        static string getClientPort(SOCKET ClientSocket);
        static void writePacket(MessageWriter *output, int msgId, char* data, unsigned int len);
        static unsigned int computeTypeLen(unsigned int len);
        static unsigned int subComputeStaticHeader(unsigned int msgId, unsigned int typeLen);
        static void sendTo(SOCKET socket, char* buffer, int length, INetworkMessage* netMessage);

    private:
        void PacketParser(Client* client);
        unsigned short getMessageId(unsigned short firstByte);
        unsigned short getMessageLengthType(unsigned short firstByte);
        unsigned short readMessageLength(unsigned short byteLenDynamicHeader, MessageReader *packet);

    protected:
        virtual void onClientConnected(SOCKET ClientSocket) = 0;
        virtual void onClientDisconnected(Client* client, int i) = 0;
        virtual void onDataReceive(Client* client, Packet* packet) = 0;

        //Client *clients; // OLD
        vector<Client*> clients;
        unsigned short max_user;
};

#endif // NETWORK_MANAGER_H
