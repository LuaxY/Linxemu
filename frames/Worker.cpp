#include "Worker.h"

pthread_t Worker::threadPtr = 0;
queue<Message> Worker::messagesQueue = queue<Message>();
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

    Worker *wok = (Worker*)&ptr;
    int i = 0;

    while(true)
    {
        if(!messagesQueue.empty())
        {
            Logger::Log(THREAD, sLog(), "Messsages queue: ", true, false);
            cout << i << endl;

            pthread_mutex_lock(&mutex_stock);
                Message process = messagesQueue.front();
                messagesQueue.pop();
            pthread_mutex_unlock(&mutex_stock);

            /** Analyse packegt here **/

            NetworkMessage *tmp;
            tmp = rawParser.parse(process.packet);

            /** Ne pour oublier de mettre cela à la fin du traitement **/
            delete tmp;
            delete process.packet;

            /** search frame here **/

            /*if(process.messageId == 182)
            {
                BasicPongMessage *pong = new BasicPongMessage;
                pong->initBasicPongMessage(true);

                MessageWriter *data = new MessageWriter();
                pong->pack(data);

                MessageWriter *answer = new MessageWriter();
                NetworkManager::writePacket(answer, pong->getMessageId(), data->getBuffer(), data->getPosition());

                send(process.client.sock, answer->getBuffer(), answer->getPosition(), 0);

                delete pong;
                delete data;
                delete answer;
            }*/

            /*if(tmp->getMessageId() == 182)
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
            }*/

            //wok->removeMessage(process);
        }

        usleep(30*1000);
    }
}

//bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, NetworkMessage* datas)
bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, Packet* packet)
{
    Message msg;

    msg.client = client;
    msg.messageId = messageId;
    msg.messageLength = messageLength;
    //msg.datas = datas;
    msg.packet = packet;

    pthread_mutex_lock(&mutex_stock);
        messagesQueue.push(msg);
    pthread_mutex_unlock(&mutex_stock);

    return true;
}

void Worker::removeMessage(Message* lastMessage)
{
}

void Worker::clearMessagesQueue()
{
    /*for(int i = 0; messagesQueue.find(i) != messagesQueue.end(); i++)
    {
        delete messagesQueue[i];
    }

    lastId = 0;*/
}
