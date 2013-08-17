#ifndef CHARACTER_MINIMAL_INFORMATIONS_H
#define CHARACTER_MINIMAL_INFORMATIONS_H

#include "../../../../utils/utils.h"
#include "../../INetworkType.h"
#include "AbstractCharacterInformation.h"

class CharacterMinimalInformations : public INetworkType, public AbstractCharacterInformation
{
public:
    void initCharacterMinimalInformations(unsigned int _id, char _level, char* _name);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 163;

    char level;
    char* name;
};

#endif // CHARACTER_MINIMAL_INFORMATIONS_H



