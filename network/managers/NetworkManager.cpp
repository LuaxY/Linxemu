#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    init();
}

NetworkManager::~NetworkManager()
{
    end();
}

void NetworkManager::init(void)
{
    #ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
    #endif
}

void NetworkManager::end(void)
{
    #ifdef WIN32
    WSACleanup();
    #endif
}

void NetworkManager::start(unsigned short port, unsigned short maxClients)
{
    clients = new Client[maxClients];

    SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET ClientSocket;
    SOCKADDR_IN ssin = {0};
    int i;
    nbClients = 0;
    fd_set rdfs;
    char buffer[1024];
    int bufferSize = 0;

    if(ServerSocket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    ssin.sin_addr.s_addr = htonl(INADDR_ANY);
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(port);

    if(bind(ServerSocket, (SOCKADDR *) &ssin, sizeof ssin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }

    if(listen(ServerSocket, maxClients) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }

    int max = ServerSocket;

    while(true)
    {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(ServerSocket, &rdfs);

        for(i = 0; i < nbClients; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        if(FD_ISSET(STDIN_FILENO, &rdfs))
        {
            break;
        }
        else if(FD_ISSET(ServerSocket, &rdfs))
        {
            SOCKADDR_IN csin = {0};
            socklen_t sinsize = sizeof csin;

            ClientSocket = accept(ServerSocket, (SOCKADDR *)&csin, &sinsize);

            if(ClientSocket == SOCKET_ERROR)
            {
                perror("accept()");
                continue;
            }

            max = ClientSocket > max ? ClientSocket : max;
            FD_SET(ClientSocket, &rdfs);

            onClientConnected(ClientSocket);
        }
        else
        {
            for(i = 0; i < nbClients; i++)
            {
                if(FD_ISSET(clients[i].sock, &rdfs))
                {
                    Client client = clients[i];
                    bufferSize = 0;

                    if((bufferSize = recv(client.sock, buffer, bufferSize - 1, 0)) < 0)
                    {
                        perror("recv()");
                    }

                    if(bufferSize == 0)
                    {
                        onClientDisconnected(client, i);
                    }
                    else
                    {
                        buffer[bufferSize] = '\0';

                        // Parse packet here

                        onDataReceive(client, buffer, bufferSize);
                    }

                    break;
                }
            }
        }
    }

    closesocket(ServerSocket);
}

string NetworkManager::getClientIP(SOCKET ClientSocket)
{
    SOCKADDR_IN csin;
    socklen_t len = sizeof(csin);
    string addressIp;

    getpeername(ClientSocket,(struct sockaddr*)&csin, &len);
    addressIp = inet_ntoa(csin.sin_addr);

    return addressIp;
}

void NetworkManager::PacketParser()
{

}
