#include "CharactersListRequestMessage.h"

INetworkMessage* CharactersListRequestMessage::getInstance() const
{
    return new CharactersListRequestMessage(*this);
}

void CharactersListRequestMessage::initCharactersListRequestMessage()
{
}

int CharactersListRequestMessage::getMessageId()
{
    return protocolId;
}

char* CharactersListRequestMessage::getMessageName()
{
    return "CharactersListRequestMessage";
}

void CharactersListRequestMessage::pack(MessageWriter *output)
{
}

void CharactersListRequestMessage::unpack(char *buffer)
{
}
