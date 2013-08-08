#include "IdentificationMessage.h"

NetworkMessage* IdentificationMessage::getInstance() const
{
    return new IdentificationMessage(*this);
}

IdentificationMessage::IdentificationMessage(IdentificationMessage* message)
{
}

void IdentificationMessage::initIdentificationMessage()
{
	_isInitialized = true;
}

bool IdentificationMessage::isInitialized()
{
	return _isInitialized;
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

void IdentificationMessage::reset()
{
	_isInitialized = false;
}
