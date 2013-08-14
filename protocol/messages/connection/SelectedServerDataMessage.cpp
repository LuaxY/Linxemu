#include "SelectedServerDataMessage.h"

INetworkMessage* SelectedServerDataMessage::getInstance() const
{
    return new SelectedServerDataMessage(*this);
}

SelectedServerDataMessage::SelectedServerDataMessage(SelectedServerDataMessage* message)
{
    serverId = message->serverId;
    address = message->address;
    port = message->port;
    canCreateNewCharacter = message->canCreateNewCharacter;
    ticket = message->ticket;
}

void SelectedServerDataMessage::initSelectedServerDataMessage(unsigned short _serverId, char* _address, unsigned short _port, bool _canCreateNewCharacter, char* _ticket)
{
    serverId = _serverId;
    address = _address;
    port = _port;
    canCreateNewCharacter = _canCreateNewCharacter;
    ticket = _ticket;

	_isInitialized = true;
}

bool SelectedServerDataMessage::isInitialized()
{
	return _isInitialized;
}

int SelectedServerDataMessage::getMessageId()
{
	return protocolId;
}

char* SelectedServerDataMessage::getMessageName()
{
	return "SelectedServerDataMessage";
}

void SelectedServerDataMessage::pack(MessageWriter *output)
{
    output->WriteUShort(serverId);
    output->WriteUTF(address);
    output->WriteUShort(port);
    output->WriteBool(canCreateNewCharacter);
    output->WriteUTF(ticket);
}

void SelectedServerDataMessage::unpack(char* buffer)
{
    MessageReader *input = new MessageReader(buffer);

	delete input;
}

void SelectedServerDataMessage::reset()
{
    serverId = 0;
    address = NULL;
    port = 0;
    canCreateNewCharacter = false;
    ticket = NULL;

	_isInitialized = false;
}
