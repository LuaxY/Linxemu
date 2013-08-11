#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <typeinfo>

#include "../utils/utils.h"
#include "../network/NetworkManager.h"
#include "../network/MessageReceiver.h"
#include "../protocol/messages/INetworkMessage.h"
#include "Frames.h"
#include "../protocol/frames/IFrame.h"
#include "../protocol/frames/framesList.h"

using namespace std;

typedef struct Message
{
    Client client;
    unsigned short messageId;
    unsigned short messageLength;
    Packet* packet;
};

class Worker
{
    public:
        Worker();
        void run();
        static bool addMessage(Client client, unsigned short messageId, unsigned short messageLength, Packet* packet);

        static queue<Message*> messagesQueue;
    private:
        void clearMessagesQueue();
        void removeMessage(INetworkMessage* netMessage, Message* message);

        static void* handler(void *ptr);
        static pthread_t threadPtr;
        static pthread_mutex_t mutex_stock;

        static MessageReceiver rawParser;
        static Frames frames;
};

#endif // WORKER_H
