#include "AuthServer.h"
#include <fstream>

AuthServer::AuthServer()
{
    Logger::Log(INFO, sLog(), "Start AuthServer ", true);

    Config* config = Config::Instance();

    requiredVersion = config->requiredVersion;
    currentVersion = config->currentVersion;
    salt = "hk2zaar9desn'@CD\"G84vF&zEK\")DT!U";

    ifstream keyFile("key.bin", ios::in | ios::binary | ios::ate);
    if(keyFile.is_open())
    {
        keySize = keyFile.tellg();
        key = new char[keySize];
        keyFile.seekg(0, ios::beg);
        keyFile.read(key, keySize);
        keyFile.close();
    }
    else
        Logger::Log(ERROR, sLog(), "Unable to open key.bin");
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
    pr.initProtocolRequired(requiredVersion, currentVersion);
    pr.pack(data);

    writePacket(packet, pr.getMessageId(), data->getBuffer(), data->getPosition());
    sendTo(c.sock, packet->getBuffer(), packet->getPosition(), pr.getInstance());

    /** Clear packet **/
    data->reset();
    packet->reset();

    /** HelloConnectMessage **/
    HelloConnectMessage hcm;
    hcm.initHelloConnectMessage(salt, key, keySize);
    hcm.pack(data);

    writePacket(packet, hcm.getMessageId(), data->getBuffer(), data->getPosition());
    sendTo(c.sock, packet->getBuffer(), packet->getPosition(), hcm.getInstance());

    /** Delete packet **/
    delete data;
    delete packet;
}

void AuthServer::onClientDisconnected(Client client, int number)
{
    Logger::Log(INFO, sLog(), "Client disconnected (" + getClientIP(client.sock) + ":" + getClientPort(client.sock) + ")");

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, Packet* packet)
{
    if(!Worker::addMessage(client, packet->messageId, packet->messageLength, packet))
    {
        Logger::Log(ERROR, sLog(), "Unable to add message ", false);
        cout << packet->messageId << " in MessagesQueue" << endl;
    }
}
