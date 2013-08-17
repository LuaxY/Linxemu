#include "CharactersListMessage.h"

INetworkMessage* CharactersListMessage::getInstance() const
{
    return new CharactersListMessage(*this);
}

void CharactersListMessage::initCharactersListMessage(bool _hasStartupActions, vector<CharacterBaseInformations*> _characters)
{
    hasStartupActions = _hasStartupActions;
    characters = _characters;
}

int CharactersListMessage::getMessageId()
{
    return protocolId;
}

char* CharactersListMessage::getMessageName()
{
    return "CharactersListMessage";
}

void CharactersListMessage::pack(MessageWriter *output)
{
    output->WriteBool(hasStartupActions);
    output->WriteUShort(characters.size());
    for(CharacterBaseInformations* entry : characters)
    {
        output->WriteUShort(entry->getTypeId());
        entry->pack(output);
    }
}

void CharactersListMessage::unpack(char *buffer)
{
}
