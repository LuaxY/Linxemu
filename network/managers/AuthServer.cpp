#include "AuthServer.h"

AuthServer::AuthServer()
{
    Logger::Log(INFO, sLog(), "Start AuthServer ", true);
}

void AuthServer::onClientConnected(SOCKET ClientSocket)
{
    Client c = {ClientSocket};
    clients[nbClients] = c;
    nbClients++;

    Logger::Log(INFO, sLog(), "Client connected (" + getClientIP(ClientSocket) + ":" + getClientPort(ClientSocket) + ")", true);

    /** Add check version client here **/
}

void AuthServer::onClientDisconnected(Client client, int number)
{
    Logger::Log(INFO, sLog(), "Client disconnected (" + getClientIP(client.sock) + ":" + getClientPort(client.sock) + ")", true);

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, Packet* packet)
{
    Logger::Log(DEBUG, sLog(), "[RCV] Message ID ", true, false);
    cout << packet->messageId << ", length " << packet->messageLength << endl;

    if(!Worker::addMessage(client, packet->messageId, packet->messageLength, packet))
    {
        Logger::Log(ERROR, sLog(), "Unable to add message ", true, false);
        cout << packet->messageId << " in MessagesQueue" << endl;
    }
}
