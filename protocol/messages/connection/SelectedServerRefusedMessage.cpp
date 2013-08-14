#include "SelectedServerRefusedMessage.h"

INetworkMessage* SelectedServerRefusedMessage::getInstance() const
{
    return new SelectedServerRefusedMessage(*this);
}

SelectedServerRefusedMessage::SelectedServerRefusedMessage(SelectedServerRefusedMessage* message)
{
    serverId = message->serverId;
    error = message->error;
    serverStatus = message->serverStatus;
}

void SelectedServerRefusedMessage::initSelectedServerRefusedMessage(unsigned short _serverId, char _error, char _serverStatus)
{
    serverId = _serverId;
    error = _error;
    serverStatus = _serverStatus;

	_isInitialized = true;
}

bool SelectedServerRefusedMessage::isInitialized()
{
	return _isInitialized;
}

int SelectedServerRefusedMessage::getMessageId()
{
	return protocolId;
}

char* SelectedServerRefusedMessage::getMessageName()
{
	return "SelectedServerRefusedMessage";
}

void SelectedServerRefusedMessage::pack(MessageWriter *output)
{
    output->WriteUShort(serverId);
    output->WriteByte(error);
    output->WriteByte(serverStatus);
}

void SelectedServerRefusedMessage::unpack(char* buffer)
{
    MessageReader *input = new MessageReader(buffer);

	delete input;
}

void SelectedServerRefusedMessage::reset()
{
    serverId = 0;
    error = 1;
    serverStatus = 1;

	_isInitialized = false;
}
