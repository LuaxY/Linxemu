#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "NetworkManager.h"
#include "../protocol/messages/INetworkMessage.h"
#include "../protocol/messages/messagesList.h"

class MessageReceiver
{
public:
    void Register();
    INetworkMessage* parse(Packet* packet);
};

class FactoryMessage
{
public:
    static void registerClass(int protocolId, INetworkMessage* obj);
    INetworkMessage* getClass(int protocolId);
    bool isPacketExist(int protocolId);

private:
    static map<int, INetworkMessage*> messagesList;
};

#endif // MESSAGE_RECEIVER_H
