#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>
#include <unistd.h>
#include <iostream>

#include "../../utils/utils.h"
#include "../managers/NetworkManager.h"
#include "NetworkMessage.h"

using namespace std;

typedef struct MessagesQueue
{
    Client client;
    unsigned short messageId;
    unsigned short messageLength;
    NetworkMessage* datas;
};

class Worker
{
    public:
        Worker();
        void run();
        static bool addMessage(Client client, unsigned short messageId, unsigned short messageLength, NetworkMessage* datas);

        static map<int, MessagesQueue*> messagesQueue;

    private:
        void clearMessagesQueue();
        void removeMessage(int id);

        static void* thread(void *ptr);
        static pthread_t threadPtr;
        static int lastId;
};

#endif // WORKER_H
