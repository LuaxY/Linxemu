#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "NetworkManager.h"
#include "../messages/NetworkMessage.h"
#include "../messages/messagesList.h"

class MessageReceiver
{
    public:
        void Register();
        NetworkMessage* parse(Packet* packet);
};

class Factory
{
    public:
        static void registerClass(int protocolId, NetworkMessage* obj);
        NetworkMessage* getClass(int protocolId);
        bool isPacketExist(int protocolId);

    private:
        static map<int, NetworkMessage*> messagesTypes;
};

#endif // MESSAGE_RECEIVER_H
