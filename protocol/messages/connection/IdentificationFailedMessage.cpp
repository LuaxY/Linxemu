#include "IdentificationFailedMessage.h"

INetworkMessage* IdentificationFailedMessage::getInstance() const
{
    return new IdentificationFailedMessage(*this);
}

void IdentificationFailedMessage::initIdentificationFailedMessage(char _reason)
{
    reason = _reason;
}

int IdentificationFailedMessage::getMessageId()
{
    return protocolId;
}

char* IdentificationFailedMessage::getMessageName()
{
    return "IdentificationFailedMessage";
}

void IdentificationFailedMessage::pack(MessageWriter *output)
{
    output->WriteByte(reason);
}

void IdentificationFailedMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    reason = input->ReadByte();

    delete input;
}
