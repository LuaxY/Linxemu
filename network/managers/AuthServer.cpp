#include "AuthServer.h"

AuthServer::AuthServer()
{
    Logger::Log(INFO, "Start AuthServer");

    rawParser.Register();
}

void AuthServer::onClientConnected(SOCKET ClientSocket)
{
    Client c = {ClientSocket};
    clients[nbClients] = c;
    nbClients++;

    Logger::Log(INFO, "Client connected (" + getClientIP(ClientSocket) + ":" + getClientPort(ClientSocket) + ")");
}

void AuthServer::onClientDisconnected(Client client, int number)
{
    Logger::Log(INFO, "Client disconnected (" + getClientIP(client.sock) + ":" + getClientPort(client.sock) + ")");

    closesocket(client.sock);
    memmove(clients + number, clients + number + 1, (nbClients - number - 1) * sizeof(Client));
    nbClients--;
}

void AuthServer::onDataReceive(Client client, Packet packet)
{
    Logger::Log(DEBUG, "[RCV] Message ID ", false);
    cout << packet.messageId << ", length " << packet.messageLength << endl;

    // unpack packet
    NetworkMessage *tmp;
    tmp = rawParser.parse(packet);

    /** Gros code a l'arrache **/
    if(tmp->getMessageId() == 182)
    {
        BasicPongMessage *pong = new BasicPongMessage;
        pong->initBasicPongMessage(true);

        MessageWriter *data = new MessageWriter();
        pong->pack(data);

        MessageWriter *answer = new MessageWriter();
        writePacket(answer, pong->getMessageId(), data->getBuffer(), data->getPosition());

        send(client.sock, answer->getBuffer(), answer->getPosition(), 0);

        delete pong;
        delete data;
        delete answer;
    }
    /** Fin du gros code à l'arrache **/

    // send packet to messagesQueue (for thread worker)


}
