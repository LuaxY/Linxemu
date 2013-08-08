#include "Worker.h"
#include <fstream>

pthread_t Worker::threadPtr = 0;
queue<Message*> Worker::messagesQueue = queue<Message*>();
pthread_mutex_t Worker::mutex_stock = PTHREAD_MUTEX_INITIALIZER;
MessageReceiver Worker::rawParser = MessageReceiver();

Worker::Worker()
{
    pthread_create(&threadPtr, NULL, &Worker::handler, this);
}

void* Worker::handler(void *ptr)
{
    Logger::Log(INFO, sLog(), "Thread Worker started successfully", true);

    rawParser.Register();
    Worker *worker = (Worker*)&ptr;

    int i = 1;

    while(true)
    {
        if(!messagesQueue.empty())
        {
            Logger::Log(THREAD, sLog(), "Messsages queue: ", true, false);
            cout << i << endl;

            pthread_mutex_lock(&mutex_stock);
                Message *message = messagesQueue.front();
                messagesQueue.pop();
            pthread_mutex_unlock(&mutex_stock);

            /** Pakcet parser **/
            NetworkMessage *netMessage;
            netMessage = rawParser.parse(message->packet);

            if(!netMessage)
            {
                Logger::Log(ERROR, sLog(), "Unknown packet ID: ", true, false);
                cout << message->packet->messageId << endl;
            }
            else
            {
                /** Frames dispatcher **/
                if(netMessage->getMessageId() == 182)
                {
                    MessageWriter *data = new MessageWriter();
                    MessageWriter *packet = new MessageWriter();

                    BasicPongMessage basicPongMessage;
                    basicPongMessage.initBasicPongMessage(true);
                    basicPongMessage.pack(data);

                    NetworkManager::writePacket(packet, basicPongMessage.getMessageId(), data->getBuffer(), data->getPosition());
                    NetworkManager::sendTo(message->client.sock, packet->getBuffer(), packet->getPosition(), basicPongMessage.getMessageId());

                    delete data;
                    delete packet;
                }
            }

            if(message->packet->messageId == 4)
            {
                Logger::Log(INFO, sLog(), "Send ClearIdentificationMessage request");

                MessageWriter *data = new MessageWriter();
                MessageWriter *packet = new MessageWriter();

                ifstream::pos_type size;
                char *newPacket;

                ifstream packetSWF("work.swf", ios::in | ios::binary | ios::ate);
                if(packetSWF.is_open())
                {
                    size = packetSWF.tellg();
                    newPacket = new char[size];
                    packetSWF.seekg(0, ios::beg);
                    packetSWF.read(newPacket, size);
                    packetSWF.close();
                }
                else
                    Logger::Log(ERROR, sLog(), "Unable to open work.swf");

                RawDataMessage rawDataMessage;
                rawDataMessage.initRawDataMessage(newPacket, size);
                rawDataMessage.pack(data);

                NetworkManager::writePacket(packet, rawDataMessage.getMessageId(), data->getBuffer(), data->getPosition());
                NetworkManager::sendTo(message->client.sock, packet->getBuffer(), packet->getPosition(), rawDataMessage.getMessageId());

                delete data;
                delete packet;
            }

            /** Delete packet **/
            worker->removeMessage(netMessage, message);

            i++;
        }

        usleep(30*1000);
    }
}

bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, Packet* packet)
{
    Message *message = new Message;

    message->client = client;
    message->messageId = messageId;
    message->messageLength = messageLength;
    message->packet = packet;

    pthread_mutex_lock(&mutex_stock);
        messagesQueue.push(message);
    pthread_mutex_unlock(&mutex_stock);

    return true;
}

void Worker::removeMessage(NetworkMessage* netMessage, Message* message)
{
    delete netMessage;
    delete message->packet;
    delete message;
}

void Worker::clearMessagesQueue()
{
    while(!messagesQueue.empty())
    {
        pthread_mutex_lock(&mutex_stock);
            Message *message = messagesQueue.front();
            messagesQueue.pop();
        pthread_mutex_unlock(&mutex_stock);

        delete message->packet;
        delete message;
    }
}
