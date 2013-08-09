#include "MessageReceiver.h"

map<int, INetworkMessage*> Factory::messagesTypes = map<int, INetworkMessage*>();

void MessageReceiver::Register()
{
    Factory::registerClass(1, new ProtocolRequired);
    Factory::registerClass(3, new HelloConnectMessage);
    Factory::registerClass(4, new IdentificationMessage);
    Factory::registerClass(182, new BasicPingMessage);
    Factory::registerClass(183, new BasicPongMessage);
    Factory::registerClass(888, new ClearIdentificationMessage);
    Factory::registerClass(6253, new RawDataMessage);
}

INetworkMessage* MessageReceiver::parse(Packet* packet)
{
    Factory storeDataManager;

    if(storeDataManager.isPacketExist(packet->messageId))
    {
        INetworkMessage *message = storeDataManager.getClass(packet->messageId);
        message->unpack(packet->buffer);
        return message;
    }

    return false;
}

void Factory::registerClass(int protocolId, INetworkMessage* obj)
{
    if(messagesTypes.find(protocolId) == messagesTypes.end())
    {
        messagesTypes[protocolId] = obj;
    }
}

INetworkMessage* Factory::getClass(int protocolId)
{
    INetworkMessage* tmp = 0;
    map<int, INetworkMessage*>::const_iterator it = messagesTypes.find(protocolId);

    if(it != messagesTypes.end())
    {
        tmp = ((*it).second)->getInstance();
    }

    return tmp;
}

bool Factory::isPacketExist(int protocolId)
{
    if(messagesTypes.find(protocolId) != messagesTypes.end())
        return true;
    else
        return false;
}
