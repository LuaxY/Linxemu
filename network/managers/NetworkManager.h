#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#ifdef WIN32

#include <winsock2.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>

using namespace std;

typedef struct Client
{
   SOCKET sock;
};

class NetworkManager
{
    public:
        NetworkManager();
        ~NetworkManager();
        bool start(unsigned short port, unsigned short maxClients);

    private:
        void init();
        void end();

    protected:
        virtual void onClientConnected(SOCKET ClientSocket) = 0;
        virtual void onClientDisconnected(Client client, int number) = 0;
        virtual void onDataReceive(Client client, char *buffer, int sizeBuffer) = 0;

        string getClientIP(SOCKET ClientSocket);

        Client *clients;
        int nbClients;
};

#endif // NETWORK_MANAGER_H
