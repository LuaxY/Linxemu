#include "MessageReceiver.h"

map<int, INetworkMessage*> FactoryMessage::messagesList = map<int, INetworkMessage*>();

void MessageReceiver::Register()
{
    FactoryMessage::registerClass(1, new ProtocolRequired);
    FactoryMessage::registerClass(3, new HelloConnectMessage);
    FactoryMessage::registerClass(4, new IdentificationMessage);
    FactoryMessage::registerClass(20, new IdentificationFailedMessage);
    FactoryMessage::registerClass(22, new IdentificationSuccessMessage);
    FactoryMessage::registerClass(30, new ServersListMessage);
    FactoryMessage::registerClass(40, new ServerSelectionMessage);
    FactoryMessage::registerClass(41, new SelectedServerRefusedMessage);
    FactoryMessage::registerClass(42, new SelectedServerDataMessage);
    FactoryMessage::registerClass(182, new BasicPingMessage);
    FactoryMessage::registerClass(183, new BasicPongMessage);
    FactoryMessage::registerClass(888, new ClearIdentificationMessage);
    FactoryMessage::registerClass(6253, new RawDataMessage);
}

INetworkMessage* MessageReceiver::parse(Packet* packet)
{
    FactoryMessage fm;

    if(fm.isPacketExist(packet->messageId))
    {
        INetworkMessage *message = fm.getClass(packet->messageId);
        message->unpack(packet->buffer);
        return message;
    }

    return false;
}

void FactoryMessage::registerClass(int protocolId, INetworkMessage* obj)
{
    if(messagesList.find(protocolId) == messagesList.end())
    {
        messagesList[protocolId] = obj;
    }
}

INetworkMessage* FactoryMessage::getClass(int protocolId)
{
    INetworkMessage* tmp = 0;
    map<int, INetworkMessage*>::const_iterator it = messagesList.find(protocolId);

    if(it != messagesList.end())
    {
        tmp = ((*it).second)->getInstance();
    }

    return tmp;
}

bool FactoryMessage::isPacketExist(int protocolId)
{
    if(messagesList.find(protocolId) != messagesList.end())
        return true;
    else
        return false;
}
