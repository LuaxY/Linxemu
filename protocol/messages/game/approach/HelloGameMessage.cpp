#include "HelloGameMessage.h"

INetworkMessage* HelloGameMessage::getInstance() const
{
	return new HelloGameMessage(*this);
}

void HelloGameMessage::initHelloGameMessage()
{
}

int HelloGameMessage::getMessageId()
{
	return protocolId;
}

char* HelloGameMessage::getMessageName()
{
	return "HelloGameMessage";
}

void HelloGameMessage::pack(MessageWriter *output)
{
}

void HelloGameMessage::unpack(char *buffer)
{
}
