#include "AuthServer.h"
#include <fstream>

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
    ProtocolRequired pr;
    pr.initProtocolRequired(1542, 1547);
    pr.pack(data);

    writePacket(packet, pr.getMessageId(), data->getBuffer(), data->getPosition());
    sendTo(c.sock, packet->getBuffer(), packet->getPosition(), pr.getMessageId());

    /** Clear packet **/
    data->reset();
    packet->reset();

    /** HelloConnectMessage (à optimiser) **/
    ifstream::pos_type size;
    char *key;

    ifstream keyFile("key.bin", ios::in | ios::binary | ios::ate);
    if(keyFile.is_open())
    {
        size = keyFile.tellg();
        key = new char[size];
        keyFile.seekg(0, ios::beg);
        keyFile.read(key, size);
        keyFile.close();
    }
    else
        Logger::Log(ERROR, sLog(), "Unable to open key.bin", true);

    HelloConnectMessage hcm;
    hcm.initHelloConnectMessage("hk2zaar9desn'@CD\"G84vF&zEK\")DT!U", key, size);
    hcm.pack(data);

    writePacket(packet, hcm.getMessageId(), data->getBuffer(), data->getPosition());
    sendTo(c.sock, packet->getBuffer(), packet->getPosition(), hcm.getMessageId());

    /** Delete packet **/
    delete[] key;
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
    Logger::Log(DEBUG, sLog(), "[RCV] Message ID ", false, false);
    cout << packet->messageId << ", " << packet->messageLength << " bytes from " << getClientIP(client.sock) << ":" << getClientPort(client.sock) << endl;

    if(!Worker::addMessage(client, packet->messageId, packet->messageLength, packet))
    {
        Logger::Log(ERROR, sLog(), "Unable to add message ", true, false);
        cout << packet->messageId << " in MessagesQueue" << endl;
    }
}
