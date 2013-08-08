#include "NetworkManager.h"
#include <stdio.h>
#include <time.h>

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
    int i, j;
    nbClients = 0;
    fd_set rdfs;
    char buffer[PACKET_MAX_SIZE];
    int bufferSize = 0;

    if(ServerSocket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    /*srand(time(NULL));

    port = ((int)rand()) % 3 + port;
    cout << port << endl;*/

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
            FD_SET(clients[i].phase, &rdfs);
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

                        for(j = 0; j <= bufferSize; j++){ client.bufferQueue.push(buffer[j]); }

                        PacketParser(client);
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

void NetworkManager::PacketParser(Client client)
{
    bool newPacket = true;

    while(newPacket)
    {
        if(client.phase == NEW_PACKET && client.bufferQueue.size() >= 2)
        {
            unsigned short staticHeader = 0;
            char header[2];

            header[0] = client.bufferQueue.front();
            client.bufferQueue.pop();
            header[1] = client.bufferQueue.front();
            client.bufferQueue.pop();

            MessageReader *headerReader = new MessageReader(header);

            staticHeader = headerReader->ReadUShort();
            client.lastMessageId = getMessageId(staticHeader);
            client.lastMessageLengthType = getMessageLengthType(staticHeader);
            client.phase = HEADER_OK;

            delete headerReader;
        }

        if(client.phase == HEADER_OK && client.bufferQueue.size() >= client.lastMessageLengthType)
        {
            char length[client.lastMessageLengthType];

            switch(client.lastMessageLengthType)
            {
                case 1:
                    length[0] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    break;
                case 2:
                    length[0] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    length[1] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    break;
                case 3:
                    length[0] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    length[1] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    length[2] = client.bufferQueue.front();
                    client.bufferQueue.pop();
                    break;
                case 0:
                default:
                    break;
            }

            MessageReader *lengthReader = new MessageReader(length);

            client.lastMessageLength = readMessageLength(client.lastMessageLengthType, lengthReader);
            client.phase = LENGTH_OK;

            delete lengthReader;
        }

        if(client.phase == LENGTH_OK && client.bufferQueue.size() >= client.lastMessageLength)
        {
            int i;
            char data[PACKET_MAX_SIZE];

            for(i = 0; i < client.lastMessageLength; i++)
            {
                data[i] = client.bufferQueue.front();
                client.bufferQueue.pop();
            }

            data[i] = '\0';

            MessageReader *dataReader = new MessageReader(data);

            Packet *packet = new Packet();
            packet->messageId = client.lastMessageId;
            packet->messageLength = client.lastMessageLength;
            packet->buffer = dataReader->ReadBytes(client.lastMessageLength);

            onDataReceive(client, packet);

            delete dataReader;

            /** Clear state **/
            client.lastMessageId = 0;
            client.lastMessageLength = 0;
            client.lastMessageLengthType = 0;
            client.phase = NEW_PACKET;

            if(client.bufferQueue.size() >= 2)
                continue;
        }

        newPacket = false;
    }
}

unsigned short NetworkManager::getMessageId(unsigned short firstByte)
{
	return firstByte >> 2;
}

unsigned short NetworkManager::getMessageLengthType(unsigned short firstByte)
{
	return firstByte & 3;
}

unsigned short NetworkManager::readMessageLength(unsigned short byteLenDynamicHeader, MessageReader *packet)
{
	unsigned short messageLength = 0;

	switch(byteLenDynamicHeader)
	{
		case 1:
			messageLength = packet->ReadByte();
			break;
		case 2:
			messageLength = packet->ReadUShort();
			break;
		case 3:
			messageLength = ((packet->ReadByte() & 255) << 16) + ((packet->ReadByte() & 255) << 8) + (packet->ReadByte() & 255);
			break;
        case 0:
        default:
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

void NetworkManager::sendTo(SOCKET socket, char* buffer, int length, NetworkMessage* netMessage)
{
    Logger::Log(DEBUG, sLog(), "[SND] ", false);
    cout << netMessage->getMessageName() << " (" << netMessage->getMessageId() << "), " << length << " bytes to " << getClientIP(socket) << ":" << getClientPort(socket) << endl;

    send(socket, buffer, length, 0);
}
