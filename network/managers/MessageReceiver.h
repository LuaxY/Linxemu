#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "NetworkManager.h"
#include "../messages/INetworkMessage.h"
#include "../messages/messagesList.h"

class MessageReceiver
{
    public:
        void Register();
        INetworkMessage* parse(Packet* packet);
};

class Factory
{
    public:
        static void registerClass(int protocolId, INetworkMessage* obj);
        INetworkMessage* getClass(int protocolId);
        bool isPacketExist(int protocolId);

    private:
        static map<int, INetworkMessage*> messagesTypes;
};

#endif // MESSAGE_RECEIVER_H
