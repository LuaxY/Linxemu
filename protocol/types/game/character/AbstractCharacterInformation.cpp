#include "AbstractCharacterInformation.h"

void AbstractCharacterInformation::initAbstractCharacterInformation(unsigned int _id)
{
    id = _id;
}

int AbstractCharacterInformation::getTypeId()
{
    return protocolId;
}

void AbstractCharacterInformation::pack(MessageWriter *output)
{
    output->WriteUInt(id);
}

void AbstractCharacterInformation::unpack(char *buffer)
{
}




