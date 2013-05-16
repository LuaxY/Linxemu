#include "BasicPingMessage.h"

NetworkMessage* BasicPingMessage::getInstance() const
{
    return new BasicPingMessage(*this);
}

void BasicPingMessage::initBasicPingMessage(bool _quiet)
{
	quiet = _quiet;

	_isInitialized = true;
}

bool BasicPingMessage::isInitialized()
{
	return _isInitialized;
}

int BasicPingMessage::getMessageId()
{
	return protocolId;
}

void BasicPingMessage::pack(MessageWriter *output)
{
	output->WriteBool(quiet);
}

void BasicPingMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	quiet = input->ReadBool();

	delete input;
}

void BasicPingMessage::reset()
{
	quiet = false;

	_isInitialized = false;
}
