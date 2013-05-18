#include "Worker.h"

pthread_t Worker::threadPtr = 0;
int Worker::lastId = 0;
map<int, MessagesQueue*> Worker::messagesQueue = map<int, MessagesQueue*>();

Worker::Worker()
{
    int ret = pthread_create(&threadPtr, NULL, &Worker::thread, this);
}

void* Worker::thread(void *ptr)
{
    Logger::Log(INFO, "Thread Worker started successfully");

    Worker *wok = (Worker*)&ptr;
    int i = 0;

    while(true)
    {
        if(messagesQueue.find(i) != messagesQueue.end())
        {
            Logger::Log(THREAD, "Messsages queue: ", false);
            cout << i << endl;

            //process in frames

            MessagesQueue *process = messagesQueue[i];

            wok->removeMessage(i);
            i++;
        }

        usleep(30*1000);
    }
}

bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, NetworkMessage* datas)
{
    MessagesQueue *msg;

    msg->client = client;
    msg->messageId = messageId;
    msg->messageLength = messageLength;
    msg->datas = datas;

    messagesQueue[lastId] = msg;

    lastId++;

    return true;
}

void Worker::removeMessage(int id)
{
    delete messagesQueue[id];
}

void Worker::clearMessagesQueue()
{
    for(int i = 0; messagesQueue.find(i) != messagesQueue.end(); i++)
    {
        delete messagesQueue[i];
    }

    lastId = 0;
}
