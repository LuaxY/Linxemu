#include "AuthServer.h"

AuthServer::AuthServer()
{
    cout << "Start AuthServer" << endl;
}

void AuthServer::onNewClient(SOCKET ClientSocket)
{
    Client c = {ClientSocket};
    clients[nbClients] = c;
    nbClients++;

    cout << "New client, IP address: " << getClientIP(ClientSocket) << endl;
}

void AuthServer::onCloseClient(Client client, int number)
{
    cout << "Close client, IP address: " << getClientIP(client.sock) << endl;

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, char *buffer, int sizeBuffer)
{
    cout << hex << buffer << endl;
    cout << "length: " << sizeBuffer << endl;
}
