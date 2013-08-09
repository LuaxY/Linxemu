#include "BasicPongMessage.h"

INetworkMessage* BasicPongMessage::getInstance() const
{
    return new BasicPongMessage(*this);
}

void BasicPongMessage::initBasicPongMessage(bool _quiet)
{
	quiet = _quiet;

	_isInitialized = true;
}

bool BasicPongMessage::isInitialized()
{
	return _isInitialized;
}

int BasicPongMessage::getMessageId()
{
	return protocolId;
}

char* BasicPongMessage::getMessageName()
{
	return "BasicPongMessage";
}

void BasicPongMessage::pack(MessageWriter *output)
{
	output->WriteBool(quiet);
}

void BasicPongMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	quiet = input->ReadBool();

	delete input;
}

void BasicPongMessage::reset()
{
	quiet = false;

	_isInitialized = false;
}

