#ifndef CHARACTER_MINIMAL_PLUS_LOOK_INFORMATIONS_H
#define CHARACTER_MINIMAL_PLUS_LOOK_INFORMATIONS_H

#include "../../../../utils/utils.h"
#include "../../INetworkType.h"
#include "CharacterMinimalInformations.h"
#include "../look/EntityLook.h"

class CharacterMinimalPlusLookInformations : public INetworkType, public CharacterMinimalInformations
{
public:
    void initCharacterMinimalPlusLookInformations(unsigned int _id, char _level, char* _name, EntityLook* _entityLook);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 163;

    EntityLook* entityLook;
};

#endif // CHARACTER_MINIMAL_PLUS_LOOK_INFORMATIONS_H


