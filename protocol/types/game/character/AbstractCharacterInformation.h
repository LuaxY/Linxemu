#ifndef ABSTRACT_CHARACTER_INFORMATION_H
#define ABSTRACT_CHARACTER_INFORMATION_H

#include "../../../../utils/utils.h"
#include "../../INetworkType.h"

class AbstractCharacterInformation : public INetworkType
{
public:
    void initAbstractCharacterInformation(unsigned int _id);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 400;

    unsigned int id;
};

#endif // ABSTRACT_CHARACTER_INFORMATION_H



