#include "IdentificationFailedMessage.h"

INetworkMessage* IdentificationFailedMessage::getInstance() const
{
    return new IdentificationFailedMessage(*this);
}

IdentificationFailedMessage::IdentificationFailedMessage(IdentificationFailedMessage* message)
{
    reason = message->reason;
}

void IdentificationFailedMessage::initIdentificationFailedMessage(char _reason)
{
    reason = _reason;

	_isInitialized = true;
}

bool IdentificationFailedMessage::isInitialized()
{
	return _isInitialized;
}

int IdentificationFailedMessage::getMessageId()
{
	return protocolId;
}

char* IdentificationFailedMessage::getMessageName()
{
	return "IdentificationFailedMessage";
}

void IdentificationFailedMessage::pack(MessageWriter *output)
{
	output->WriteByte(reason);
}

void IdentificationFailedMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	reason = input->ReadByte();

	delete input;
}

void IdentificationFailedMessage::reset()
{
	reason = '\99';

	_isInitialized = false;
}
