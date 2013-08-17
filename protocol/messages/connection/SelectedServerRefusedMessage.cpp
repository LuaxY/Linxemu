#include "SelectedServerRefusedMessage.h"

INetworkMessage* SelectedServerRefusedMessage::getInstance() const
{
    return new SelectedServerRefusedMessage(*this);
}

void SelectedServerRefusedMessage::initSelectedServerRefusedMessage(unsigned short _serverId, char _error, char _serverStatus)
{
    serverId = _serverId;
    error = _error;
    serverStatus = _serverStatus;
}

int SelectedServerRefusedMessage::getMessageId()
{
    return protocolId;
}

char* SelectedServerRefusedMessage::getMessageName()
{
    return "SelectedServerRefusedMessage";
}

void SelectedServerRefusedMessage::pack(MessageWriter *output)
{
    output->WriteUShort(serverId);
    output->WriteByte(error);
    output->WriteByte(serverStatus);
}

void SelectedServerRefusedMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    serverId = input->ReadUShort();
    error = input->ReadByte();
    serverStatus = input->ReadByte();

    delete input;
}
