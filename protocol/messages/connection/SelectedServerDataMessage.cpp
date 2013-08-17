#include "SelectedServerDataMessage.h"

INetworkMessage* SelectedServerDataMessage::getInstance() const
{
    return new SelectedServerDataMessage(*this);
}

void SelectedServerDataMessage::initSelectedServerDataMessage(unsigned short _serverId, char* _address, unsigned short _port, bool _canCreateNewCharacter, char* _ticket)
{
    serverId = _serverId;
    address = _address;
    port = _port;
    canCreateNewCharacter = _canCreateNewCharacter;
    ticket = _ticket;
}

int SelectedServerDataMessage::getMessageId()
{
    return protocolId;
}

char* SelectedServerDataMessage::getMessageName()
{
    return "SelectedServerDataMessage";
}

void SelectedServerDataMessage::pack(MessageWriter *output)
{
    output->WriteUShort(serverId);
    output->WriteUTF(address);
    output->WriteUShort(port);
    output->WriteBool(canCreateNewCharacter);
    output->WriteUTF(ticket);
}

void SelectedServerDataMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    serverId = input->ReadUShort();
    address = input->ReadUTF();
    port = input->ReadUShort();
    canCreateNewCharacter = input->ReadBool();
    ticket = input->ReadUTF();

    delete input;
}
