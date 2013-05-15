#include "AuthServer.h"

AuthServer::AuthServer()
{
    Logger::Log(INFO, "Start AuthServer");
}

void AuthServer::onClientConnected(SOCKET ClientSocket)
{
    Client c = {ClientSocket};
    clients[nbClients] = c;
    nbClients++;

    Logger::Log(INFO, "New client, IP address: " + getClientIP(ClientSocket));
}

void AuthServer::onClientDisconnected(Client client, int number)
{
    Logger::Log(INFO, "Close client, IP address: " + getClientIP(client.sock));

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, Packet packet)
{
    Logger::Log(DEBUG, "[RCV] Message ID ", false);
    cout << packet.messageId << ", length " << packet.messageLength << endl;

    // send packet to messagesQueue (for thread worker)
}
