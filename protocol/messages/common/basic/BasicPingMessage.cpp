#include "BasicPingMessage.h"

INetworkMessage* BasicPingMessage::getInstance() const
{
	return new BasicPingMessage(*this);
}

void BasicPingMessage::initBasicPingMessage(bool _quiet)
{
	quiet = _quiet;
}

int BasicPingMessage::getMessageId()
{
	return protocolId;
}

char* BasicPingMessage::getMessageName()
{
	return "BasicPingMessage";
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
