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
    if(clients.size() >= max_user)
    {
        IdentificationFailedMessage ifm;
        ifm.initIdentificationFailedMessage(5);
        sendTo(ClientSocket, ifm.getInstance());
    }
    else
    {
        Client *newClient = new Client;
        newClient->socket = ClientSocket;
        clients.push_back(newClient);

        Logger::Log(INFO, sLog(), "Client connected (" + getClientIP(ClientSocket) + ":" + getClientPort(ClientSocket) + ")", true);

        ProtocolRequired pr;
        pr.initProtocolRequired(requiredVersion, currentVersion);
        sendTo(newClient->socket, pr.getInstance());

        newClient->salt = genSalt(32);

        HelloConnectMessage hcm;
        hcm.initHelloConnectMessage(newClient->salt, key, keySize);
        sendTo(newClient->socket, hcm.getInstance());
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
