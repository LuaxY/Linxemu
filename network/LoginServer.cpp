#include "LoginServer.h"
#include <fstream>

LoginServer::LoginServer()
{
    Logger::Log(INFO, sLog(), "Start LoginServer ", true);

    Config* config = Config::Instance();

    requiredVersion = config->requiredVersion;
    currentVersion = config->currentVersion;

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

void LoginServer::onClientConnected(SOCKET ClientSocket)
{
    MessageWriter *data = new MessageWriter();
    MessageWriter *packet = new MessageWriter();

    if(clients.size() >= max_user)
    {
        IdentificationFailedMessage ifm;
        ifm.initIdentificationFailedMessage(5);
        ifm.pack(data);

        writePacket(packet, ifm.getMessageId(), data->getBuffer(), data->getPosition());
        sendTo(ClientSocket, packet->getBuffer(), packet->getPosition(), ifm.getInstance());
    }
    else
    {
        Client *newClient = new Client;
        newClient->socket = ClientSocket;
        clients.push_back(newClient);

        Logger::Log(INFO, sLog(), "Client connected (" + getClientIP(ClientSocket) + ":" + getClientPort(ClientSocket) + ")", true);

        /** ProtocolRequired **/
        ProtocolRequired pr;
        pr.initProtocolRequired(requiredVersion, currentVersion);
        pr.pack(data);

        writePacket(packet, pr.getMessageId(), data->getBuffer(), data->getPosition());
        sendTo(newClient->socket, packet->getBuffer(), packet->getPosition(), pr.getInstance());

        /** Clear packet **/
        data->reset();
        packet->reset();

        /** HelloConnectMessage **/
        newClient->salt = genSalt(32);

        HelloConnectMessage hcm;
        hcm.initHelloConnectMessage(newClient->salt, key, keySize);
        hcm.pack(data);

        writePacket(packet, hcm.getMessageId(), data->getBuffer(), data->getPosition());
        sendTo(newClient->socket, packet->getBuffer(), packet->getPosition(), hcm.getInstance());

        /** Delete packet **/
        delete data;
        delete packet;
    }
}

void LoginServer::onClientDisconnected(Client* client, int i)
{
    Logger::Log(INFO, sLog(), "Client disconnected (" + getClientIP(client->socket) + ":" + getClientPort(client->socket) + ")");

    closesocket(client->socket);
    clients.erase(clients.begin()+i);
    delete client;
}

void LoginServer::onDataReceive(Client* client, Packet* packet)
{
    if(!Worker::addMessage(client, packet->messageId, packet->messageLength, packet))
    {
        Logger::Log(ERROR, sLog(), "Unable to add message ", false);
        cout << packet->messageId << " in MessagesQueue" << endl;
    }
}
