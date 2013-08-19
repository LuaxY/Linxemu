#include "AccountCapabilitiesMessage.h"

INetworkMessage* AccountCapabilitiesMessage::getInstance() const
{
    return new AccountCapabilitiesMessage(*this);
}

void AccountCapabilitiesMessage::initAccountCapabilitiesMessage(unsigned int _accountId, bool _tutorialAvailable, unsigned short _breedsVisible, unsigned short _breedsAvailable, char _status)
{
    accountId = _accountId;
    tutorialAvailable = _tutorialAvailable;
    breedsVisible = _breedsVisible;
    breedsAvailable = _breedsAvailable;
    status = _status;
}

int AccountCapabilitiesMessage::getMessageId()
{
    return protocolId;
}

char* AccountCapabilitiesMessage::getMessageName()
{
    return "AccountCapabilitiesMessage";
}

void AccountCapabilitiesMessage::pack(MessageWriter *output)
{
    output->WriteUInt(accountId);
    output->WriteBool(tutorialAvailable);
    output->WriteUShort(breedsVisible);
    output->WriteUShort(breedsAvailable);
    output->WriteByte(status);
}

void AccountCapabilitiesMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    accountId = input->ReadUInt();
    tutorialAvailable = input->ReadBool();
    breedsVisible = input->ReadUShort();
    breedsAvailable = input->ReadUShort();
    status = input->ReadByte();

    delete input;
}
