#ifndef CHARACTERS_LIST_MESSAGE_H
#define CHARACTERS_LIST_MESSAGE_H

#include "../../../../../utils/utils.h"
#include "../../../INetworkMessage.h"
#include "../../../../types/game/character/choice/CharacterBaseInformations.h"
#include <vector>

class CharactersListMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initCharactersListMessage(bool _hasStartupActions, vector<CharacterBaseInformations*> _characters);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 151;

    bool hasStartupActions;
    vector<CharacterBaseInformations*> characters;
};

#endif // CHARACTERS_LIST_MESSAGE_H
