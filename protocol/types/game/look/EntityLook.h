#ifndef ENTITY_LOOK_H
#define ENTITY_LOOK_H

#include "../../../../utils/utils.h"
#include "../../INetworkType.h"
#include "SubEntity.h"
#include <vector>

class EntityLook : public INetworkType
{
public:
    void initEntityLook(unsigned short _bonesId, vector<int> _skins, vector<int> _indexedColors, vector<int> _scales, vector<SubEntity*> _subentities);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 55;

    unsigned short bonesId;
    vector<int> skins;
    vector<int> indexedColors;
    vector<int> scales;
    vector<SubEntity*> subentities;
};

#endif // ENTITY_LOOK_H
