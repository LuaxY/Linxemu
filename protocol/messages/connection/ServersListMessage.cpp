#include "ServersListMessage.h"

INetworkMessage* ServersListMessage::getInstance() const
{
	return new ServersListMessage(*this);
}

void ServersListMessage::initServersListMessage(vector<GameServerInformations*> _servers)
{
	servers = _servers;
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

void ServersListMessage::unpack(char *buffer)
{
	MessageReader *input = new MessageReader(buffer);

	delete input;
}
