#ifndef SUB_ENTITY_H
#define SUB_ENTITY_H

#include "../../../../utils/utils.h"
#include "../../INetworkType.h"
#include <vector>

class SubEntity : public INetworkType
{
public:
    void initSubEntity();

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 54;
};

#endif // SUB_ENTITY_H

