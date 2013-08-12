#include "ServersListMessage.h"

INetworkMessage* ServersListMessage::getInstance() const
{
    return new ServersListMessage(*this);
}

ServersListMessage::ServersListMessage(ServersListMessage* message)
{
    servers = message->servers;
}

void ServersListMessage::initServersListMessage(vector<GameServerInformations*> _servers)
{
    servers = _servers;

	_isInitialized = true;
}

bool ServersListMessage::isInitialized()
{
	return _isInitialized;
}

int ServersListMessage::getMessageId()
{
	return protocolId;
}

char* ServersListMessage::getMessageName()
{
	return "ServersListMessage";
}

void ServersListMessage::pack(MessageWriter *output)
{
    output->WriteUShort(servers.size());
    for(GameServerInformations entry : servers)
    {
        entry.pack(output);
    }
}

void ServersListMessage::unpack(char* buffer)
{
    MessageReader *input = new MessageReader(buffer);

	delete input;
}

void ServersListMessage::reset()
{
    servers.clear();

	_isInitialized = false;
}
