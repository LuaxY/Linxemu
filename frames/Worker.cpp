#include "Worker.h"

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
                Logger::Log(ERROR, sLog(), "Unknown packet Id ", true, false);
                cout << message->packet->messageId << endl;
            }
            else
            {
                /** Frames dispatcher **/
                if(netMessage->getMessageId() == 182)
                {
                    BasicPongMessage *pong = new BasicPongMessage;
                    pong->initBasicPongMessage(true);

                    MessageWriter *data = new MessageWriter();
                    pong->pack(data);

                    MessageWriter *answer = new MessageWriter();
                    NetworkManager::writePacket(answer, pong->getMessageId(), data->getBuffer(), data->getPosition());

                    send(message->client.sock, answer->getBuffer(), answer->getPosition(), 0);

                    delete pong;
                    delete data;
                    delete answer;
                }
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
