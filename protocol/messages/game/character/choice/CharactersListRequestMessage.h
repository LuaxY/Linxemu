#ifndef CHARACTERS_LIST_REQUEST_MESSAGE_H
#define CHARACTERS_LIST_REQUEST_MESSAGE_H

#include "../../../../../utils/utils.h"
#include "../../../INetworkMessage.h"

class CharactersListRequestMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initCharactersListRequestMessage();

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 150;

};

#endif // CHARACTERS_LIST_REQUEST_MESSAGE_H
