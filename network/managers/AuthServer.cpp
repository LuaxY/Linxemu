#include "AuthServer.h"

AuthServer::AuthServer()
{
    Log(INFO, "Start AuthServer");
}

void AuthServer::onClientConnected(SOCKET ClientSocket)
{
    Client c = {ClientSocket};
    clients[nbClients] = c;
    nbClients++;

    Log(INFO, "New client, IP address: " + string(getClientIP(ClientSocket)));
}

void AuthServer::onClientDisconnected(Client client, int number)
{
    Log(INFO, "Close client, IP address: " + string(getClientIP(client.sock)));

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, char *buffer, int bufferSize)
{
    Log(DEBUG, "Packet X");
    cout << hex << buffer << endl;
    cout << "length: " << bufferSize << endl;
}
