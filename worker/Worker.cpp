#include "Worker.h"
#include <fstream>

pthread_t Worker::threadPtr = 0;
queue<Message*> Worker::messagesQueue = queue<Message*>();
pthread_mutex_t Worker::mutex_stock = PTHREAD_MUTEX_INITIALIZER;
MessageReceiver Worker::rawParser = MessageReceiver();
Frames Worker::frames = Frames();

Worker::Worker()
{
    pthread_create(&threadPtr, NULL, &Worker::handler, this);
}

void* Worker::handler(void *ptr)
{
    Logger::Log(INFO, sLog(), "Thread Worker started successfully", true);

    rawParser.Register();
    frames.Register();
    Worker* worker = (Worker*)&ptr;

    int i = 1;

    while(true)
    {
        if(!messagesQueue.empty())
        {
            pthread_mutex_lock(&mutex_stock);
            Message *message = messagesQueue.front();
            messagesQueue.pop();
            pthread_mutex_unlock(&mutex_stock);

            /** Pakcet parser **/
            INetworkMessage *netMessage;
            netMessage = rawParser.parse(message->packet);

            if(!netMessage)
            {
                Logger::Log(ERROR, sLog(), "Unknown packet ID: ", false);
                cout << message->packet->messageId << endl;
            }
            else
            {
                Logger::Log(DEBUG, sLog(), "[RCV] ", false);
                cout << netMessage->getMessageName() << " (" << netMessage->getMessageId() << "), " << message->messageLength << " bytes from " << NetworkManager::getClientIP(message->client->socket) << ":" << NetworkManager::getClientPort(message->client->socket) << endl;

                /** Frames dispatcher **/
                if(!frames.processMessage(netMessage, message->client))
                    Logger::Log(ERROR, sLog(), "No frame could not resolve the message");
            }

            /** Delete packet **/
            worker->removeMessage(netMessage, message);

            i++;
        }

        usleep(30*1000);
    }
}

bool Worker::addMessage(Client* client, unsigned short messageId, unsigned short messageLength, Packet* packet)
{
    Message* message = new Message;

    message->client = client;
    message->messageId = messageId;
    message->messageLength = messageLength;
    message->packet = packet;

    pthread_mutex_lock(&mutex_stock);
    messagesQueue.push(message);
    pthread_mutex_unlock(&mutex_stock);

    return true;
}

void Worker::removeMessage(INetworkMessage* netMessage, Message* message)
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
