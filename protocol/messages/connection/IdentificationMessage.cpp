#include "IdentificationMessage.h"

INetworkMessage* IdentificationMessage::getInstance() const
{
	return new IdentificationMessage(*this);
}

void IdentificationMessage::initIdentificationMessage()
{
}

int IdentificationMessage::getMessageId()
{
	return protocolId;
}

char* IdentificationMessage::getMessageName()
{
	return "IdentificationMessage";
}

void IdentificationMessage::pack(MessageWriter *output)
{
}

void IdentificationMessage::unpack(char *buffer)
{
	MessageReader *input = new MessageReader(buffer);

	delete input;
}
