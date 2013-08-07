#include "AuthServer.h"
#include <vector>
#include <stdio.h>
#include <time.h>

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

    MessageWriter *data = new MessageWriter();
    MessageWriter *packet = new MessageWriter();

    /** ProtocolRequired **/
    ProtocolRequired protocolRequired;
    protocolRequired.initProtocolRequired(1542, 1547);
    protocolRequired.pack(data);

    NetworkManager::writePacket(packet, protocolRequired.getMessageId(), data->getBuffer(), data->getPosition());
    send(c.sock, packet->getBuffer(), packet->getPosition(), 0);

    /** Clear packet **/
    data->reset();
    packet->reset();

    /** HelloConnectMessage **/
    vector<int> noRSA;

    srand(time(NULL));

    for(int i = 0; i < 127; i++)
	{
        noRSA.push_back(((int)rand())%256);
	}

    HelloConnectMessage helloConnectMessage;
    helloConnectMessage.initHelloConnectMessage("2k2dhdRI9ueBwtZl5ImJpDiahw31jpK1", noRSA);
    helloConnectMessage.pack(data);

    NetworkManager::writePacket(packet, helloConnectMessage.getMessageId(), data->getBuffer(), data->getPosition());
    send(c.sock, packet->getBuffer(), packet->getPosition(), 0);

    /** Delete packet **/
    delete data;
    delete packet;
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
