#include "ServerSelectionMessage.h"

INetworkMessage* ServerSelectionMessage::getInstance() const
{
	return new ServerSelectionMessage(*this);
}

void ServerSelectionMessage::initServerSelectionMessage(unsigned short _serverId)
{
	serverId = _serverId;
}

int ServerSelectionMessage::getMessageId()
{
	return protocolId;
}

char* ServerSelectionMessage::getMessageName()
{
	return "ServerSelectionMessage";
}

void ServerSelectionMessage::pack(MessageWriter *output)
{
	output->WriteUShort(serverId);
}

void ServerSelectionMessage::unpack(char *buffer)
{
	MessageReader *input = new MessageReader(buffer);

	serverId = input->ReadUShort();

	delete input;
}
