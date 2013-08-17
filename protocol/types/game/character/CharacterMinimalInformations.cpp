#include "CharacterMinimalInformations.h"

void CharacterMinimalInformations::initCharacterMinimalInformations(unsigned int _id, char _level, char* _name)
{
    AbstractCharacterInformation::initAbstractCharacterInformation(_id);
    level = _level;
    name = _name;
}

int CharacterMinimalInformations::getTypeId()
{
    return protocolId;
}

void CharacterMinimalInformations::pack(MessageWriter *output)
{
    AbstractCharacterInformation::pack(output);
    output->WriteByte(level);
    output->WriteUTF(name);
}

void CharacterMinimalInformations::unpack(char *buffer)
{
}



