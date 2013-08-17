#include "EntityLook.h"

void EntityLook::initEntityLook(unsigned short _bonesId, vector<int> _skins, vector<int> _indexedColors, vector<int> _scales, vector<SubEntity*> _subentities)
{
    bonesId = _bonesId;
    skins = _skins;
    indexedColors = _indexedColors;
    scales = _scales;
    subentities = _subentities;
}

int EntityLook::getTypeId()
{
    return protocolId;
}

void EntityLook::pack(MessageWriter *output)
{
    output->WriteUShort(bonesId);

    output->WriteUShort(skins.size());
    for(int entry : skins)
    {
        output->WriteInt(entry);
    }

    output->WriteUShort(indexedColors.size());
    for(int entry : indexedColors)
    {
        output->WriteInt(entry);
    }

    output->WriteUShort(subentities.size());
    for(SubEntity* entry : subentities)
    {
        entry->pack(output);
    }
}

void EntityLook::unpack(char *buffer)
{
}
