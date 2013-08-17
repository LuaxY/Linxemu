#ifndef CHARACTER_BASE_INFORMATIONS_H
#define CHARACTER_BASE_INFORMATIONS_H

#include "../../../../../utils/utils.h"
#include "../../../INetworkType.h"
#include "../CharacterMinimalPlusLookInformations.h"

class CharacterBaseInformations : public INetworkType, public CharacterMinimalPlusLookInformations
{
public:
    void initCharacterBaseInformations(unsigned int _id, char _level, char* _name, EntityLook* _entityLook, char _breed, bool _sex);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 45;

    char breed;
    bool sex;
};

#endif // CHARACTER_BASE_INFORMATIONS_H

