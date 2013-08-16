#include "GameServer.h"
#include <fstream>

GameServer::GameServer()
{
	Logger::Log(INFO, sLog(), "Start GameServer ", true);

	Config* config = Config::Instance();

}

void GameServer::onClientConnected(SOCKET ClientSocket)
{
	MessageWriter *data = new MessageWriter();
	MessageWriter *packet = new MessageWriter();

	if(clients.size() >= max_user)
	{

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

		/** HelloGameMessage **/
		HelloGameMessage hgm;
		hgm.initHelloGameMessage();
		hgm.pack(data);

		writePacket(packet, hgm.getMessageId(), data->getBuffer(), data->getPosition());
		sendTo(newClient->socket, packet->getBuffer(), packet->getPosition(), hgm.getInstance());

		/** Delete packet **/
		delete data;
		delete packet;
	}
}

void GameServer::onClientDisconnected(Client* client, int i)
{
    Logger::Log(INFO, sLog(), "Client disconnected (" + getClientIP(client->socket) + ":" + getClientPort(client->socket) + ")");

    closesocket(client->socket);
    clients.erase(clients.begin()+i);
    delete client;
}

void GameServer::onDataReceive(Client* client, Packet* packet)
{
    if(!Worker::addMessage(client, packet->messageId, packet->messageLength, packet))
    {
        Logger::Log(ERROR, sLog(), "Unable to add message ", false);
        cout << packet->messageId << " in MessagesQueue" << endl;
    }
}
