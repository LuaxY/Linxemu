#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "NetworkManager.h"
#include "../messages/NetworkMessage.h"

#include "../messages/common/basic/BasicPingMessage.h"

class MessageReceiver
{
    public:
        void Register();
        NetworkMessage* parse(Packet packet);
};

class Factory
{
    public:
        static void registerClass(const int protocolId, NetworkMessage* obj);
        NetworkMessage* getClass(const int protocolId) const;

    private:
        static map<int, NetworkMessage*> messagesTypes;
};

#endif // MESSAGE_RECEIVER_H
