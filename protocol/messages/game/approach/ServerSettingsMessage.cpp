#include "ServerSettingsMessage.h"

INetworkMessage* ServerSettingsMessage::getInstance() const
{
    return new ServerSettingsMessage(*this);
}

void ServerSettingsMessage::initServerSettingsMessage(char* _lang, char _community, char _gameType)
{
    lang = _lang;
    community = _community;
    gameType = _gameType;
}

int ServerSettingsMessage::getMessageId()
{
    return protocolId;
}

char* ServerSettingsMessage::getMessageName()
{
    return "ServerSettingsMessage";
}

void ServerSettingsMessage::pack(MessageWriter *output)
{
    output->WriteUTF(lang);
    output->WriteByte(community);
    output->WriteByte(gameType);
}

void ServerSettingsMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    lang = input->ReadUTF();
    community = input->ReadByte();
    gameType = input->ReadByte();

    delete input;
}
