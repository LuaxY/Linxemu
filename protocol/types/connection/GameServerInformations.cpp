#include "GameServerInformations.h"

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
}
