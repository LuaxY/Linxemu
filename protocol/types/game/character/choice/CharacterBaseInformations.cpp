#include "CharacterBaseInformations.h"

void CharacterBaseInformations::initCharacterBaseInformations(unsigned int _id, char _level, char* _name, EntityLook* _entityLook, char _breed, bool _sex)
{
    CharacterMinimalPlusLookInformations::initCharacterMinimalPlusLookInformations(_id, _level, _name, _entityLook);
    breed = _breed;
    sex = _sex;
}

int CharacterBaseInformations::getTypeId()
{
    return protocolId;
}

void CharacterBaseInformations::pack(MessageWriter *output)
{
    CharacterMinimalPlusLookInformations::pack(output);
    output->WriteByte(breed);
    output->WriteBool(sex);
}

void CharacterBaseInformations::unpack(char *buffer)
{
}

