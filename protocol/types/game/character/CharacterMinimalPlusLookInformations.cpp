#include "CharacterMinimalPlusLookInformations.h"

void CharacterMinimalPlusLookInformations::initCharacterMinimalPlusLookInformations(unsigned int _id, char _level, char* _name, EntityLook* _entityLook)
{
    CharacterMinimalPlusLookInformations::initCharacterMinimalInformations(_id, _level, _name);
    entityLook = _entityLook;
}

int CharacterMinimalPlusLookInformations::getTypeId()
{
    return protocolId;
}

void CharacterMinimalPlusLookInformations::pack(MessageWriter *output)
{
    CharacterMinimalInformations::pack(output);
    entityLook->pack(output);
}

void CharacterMinimalPlusLookInformations::unpack(char *buffer)
{
}


