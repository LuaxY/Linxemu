#include "GameServerInformations.h"

GameServerInformations::GameServerInformations(GameServerInformations* message)
{
    id = message->id;
    status = message->status;
    completion = message->completion;
    isSelectable = message->isSelectable;
    charactersCount = message->charactersCount;
    date = message->date;
}

void GameServerInformations::initGameServerInformations(unsigned short _id, char _status, char _completion, bool _isSelectable, char _charactersCount, long _date)
{
    id = _id;
    status = _status;
    completion = _completion;
    isSelectable = _isSelectable;
    charactersCount = _charactersCount;
    date = _date;
}

int GameServerInformations::getTypeId()
{
	return protocolId;
}

void GameServerInformations::pack(MessageWriter *output)
{
    output->WriteUShort(id);
    output->WriteByte(status);
    output->WriteByte(completion);
    output->WriteBool(isSelectable);
    output->WriteByte(charactersCount);
    output->WriteULong(date);
}

void GameServerInformations::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	delete input;
}

void GameServerInformations::reset()
{
    id = 0;
    status = 1;
    completion = 0;
    isSelectable = false;
    charactersCount = 0;
    date = 0;
}
