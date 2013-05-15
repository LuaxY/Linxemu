#include "BasicPingMessage.h"

BasicPingMessage::BasicPingMessage() : _isInitialized(false)
{
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

void BasicPingMessage::unpack(MessageReader *input)
{
	quiet = input->ReadBool();
}

void BasicPingMessage::reset()
{
	quiet = false;
}
