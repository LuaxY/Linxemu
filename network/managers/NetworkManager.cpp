#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::start(unsigned short port, unsigned short maxClients)
{
    clients = new Client[maxClients];

    SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET ClientSocket;
    SOCKADDR_IN ssin = {0};
    int i;
    nbClients = 0;
    fd_set rdfs;
    char buffer[1024];
    int bufferSize = 0;

    if(ServerSocket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    ssin.sin_addr.s_addr = htonl(INADDR_ANY);
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(port);

    if(bind(ServerSocket, (SOCKADDR *) &ssin, sizeof ssin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }

    if(listen(ServerSocket, maxClients) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }

    int max = ServerSocket;

    while(true)
    {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(ServerSocket, &rdfs);

        for(i = 0; i < nbClients; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        if(FD_ISSET(STDIN_FILENO, &rdfs))
        {
            break;
        }
        else if(FD_ISSET(ServerSocket, &rdfs))
        {
            SOCKADDR_IN csin = {0};
            socklen_t sinsize = sizeof csin;

            ClientSocket = accept(ServerSocket, (SOCKADDR *)&csin, &sinsize);

            if(ClientSocket == SOCKET_ERROR)
            {
                perror("accept()");
                continue;
            }

            max = ClientSocket > max ? ClientSocket : max;
            FD_SET(ClientSocket, &rdfs);

            onClientConnected(ClientSocket);
        }
        else
        {
            for(i = 0; i < nbClients; i++)
            {
                if(FD_ISSET(clients[i].sock, &rdfs))
                {
                    Client client = clients[i];
                    bufferSize = 0;

                    if((bufferSize = recv(client.sock, buffer, bufferSize - 1, 0)) < 0)
                    {
                        perror("recv()");
                    }

                    if(bufferSize == 0)
                    {
                        onClientDisconnected(client, i);
                    }
                    else
                    {
                        buffer[bufferSize] = '\0';

                        // Parse packet here
                        PacketParser(client, buffer, bufferSize);


                    }

                    break;
                }
            }
        }
    }

    closesocket(ServerSocket);
}

string NetworkManager::getClientIP(SOCKET ClientSocket)
{
    SOCKADDR_IN csin;
    socklen_t len = sizeof(csin);
    string addressIp;

    getpeername(ClientSocket,(struct sockaddr*)&csin, &len);
    addressIp = inet_ntoa(csin.sin_addr);

    return addressIp;
}

string NetworkManager::getClientPort(SOCKET ClientSocket)
{
    SOCKADDR_IN csin;
    socklen_t len = sizeof(csin);
    unsigned short port;

    getpeername(ClientSocket,(struct sockaddr*)&csin, &len);
    port = ntohs(csin.sin_port);

    stringstream portString;
    portString << port;

    return portString.str();
}

void NetworkManager::PacketParser(Client client, char *buffer, int bufferSize)
{
    unsigned short staticHeader = 0;
    unsigned short messageId = 0;
    unsigned short messageLength = 0;

    MessageReader *packets = new MessageReader(buffer);

    while(packets->bytesAvailable() > 0)
    {
        staticHeader = packets->ReadUShort();
        messageId = getMessageId(staticHeader);
        messageLength = readMessageLength(staticHeader, packets);

        Packet packet;
        packet.messageId = messageId;
        packet.messageLength = messageLength;
        packet.buffer = packets->ReadBytes(messageLength);

        onDataReceive(client, packet);
    }

    delete packets;
}

unsigned short NetworkManager::getMessageId(unsigned short firstOctet)
{
	return firstOctet >> 2;
}

unsigned short NetworkManager::readMessageLength(unsigned short staticHeader, MessageReader *packet)
{
	unsigned int byteLenDynamicHeader = staticHeader & 3;
	unsigned short messageLength = 0;

	switch(byteLenDynamicHeader)
	{
		case 0:
			break;
		case 1:
			messageLength = packet->ReadByte();
			break;
		case 2:
			messageLength = packet->ReadUShort();
			break;
		case 3:
			messageLength = ((packet->ReadByte() & 255) << 16) + ((packet->ReadByte() & 255) << 8) + (packet->ReadByte() & 255);
			break;
	}

	return messageLength;
}

void NetworkManager::writePacket(MessageWriter *output, int msgId, char* data, unsigned int len)
{
    unsigned int typeLen = computeTypeLen(len);
    output->WriteShort(subComputeStaticHeader(msgId, typeLen));

    switch(typeLen)
    {
        case 0:
            return;
            break;
        case 1:
            output->WriteByte(len);
            break;
        case 2:
            output->WriteShort(len);
            break;
        case 3:
            // Motherfucker
            break;
    }

    output->WriteBytes(data, len);
}

unsigned int NetworkManager::computeTypeLen(unsigned int len)
{
    if(len > 65535)
        return 3;
    if(len > 255)
        return 2;
    if(len > 0)
        return 1;

    return 0;
}

unsigned int NetworkManager::subComputeStaticHeader(unsigned int msgId, unsigned int typeLen)
{
    return msgId << 2 | typeLen;
}
