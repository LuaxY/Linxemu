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

    for(int i = 0; true; i++)
    {
        if(!messagesQueue.empty())
        {
            Logger::Log(THREAD, sLog(), "Messsages queue: ", true, false);
            cout << i << endl;

            pthread_mutex_lock(&mutex_stock);
                Message *process = messagesQueue.front();
                messagesQueue.pop();
            pthread_mutex_unlock(&mutex_stock);

            /** Analyse packegt here **/

            NetworkMessage *tmp;
            tmp = rawParser.parse(process->packet);

            /** search frame here **/

            if(tmp->getMessageId() == 182)
            {
                BasicPongMessage *pong = new BasicPongMessage;
                pong->initBasicPongMessage(true);

                MessageWriter *data = new MessageWriter();
                pong->pack(data);

                MessageWriter *answer = new MessageWriter();
                NetworkManager::writePacket(answer, pong->getMessageId(), data->getBuffer(), data->getPosition());

                send(process->client.sock, answer->getBuffer(), answer->getPosition(), 0);

                delete pong;
                delete data;
                delete answer;
            }

            /** Delete packet **/
            worker->removeMessage(tmp, process);
        }

        usleep(30*1000);
    }
}

bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, Packet* packet)
{
    Message *msg = new Message;

    msg->client = client;
    msg->messageId = messageId;
    msg->messageLength = messageLength;
    msg->packet = packet;

    pthread_mutex_lock(&mutex_stock);
        messagesQueue.push(msg);
    pthread_mutex_unlock(&mutex_stock);

    return true;
}

void Worker::removeMessage(NetworkMessage* packet, Message* message)
{
    pLog();
    delete packet;
    delete message->packet;
    delete message;
}

void Worker::clearMessagesQueue()
{
    /*for(int i = 0; messagesQueue.find(i) != messagesQueue.end(); i++)
    {
        delete messagesQueue[i];
    }

    lastId = 0;*/
}
