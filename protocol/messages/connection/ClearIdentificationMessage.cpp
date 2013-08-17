#include "ClearIdentificationMessage.h"

INetworkMessage* ClearIdentificationMessage::getInstance() const
{
    return new ClearIdentificationMessage(*this);
}

void ClearIdentificationMessage::initClearIdentificationMessage(char* _user, char* _password)
{
    user = _user;
    password = _password;
}

int ClearIdentificationMessage::getMessageId()
{
    return protocolId;
}

char* ClearIdentificationMessage::getMessageName()
{
    return "ClearIdentificationMessage";
}

void ClearIdentificationMessage::pack(MessageWriter *output)
{
    output->WriteUTF(user);
    output->WriteUTF(password);
}

void ClearIdentificationMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

    user = input->ReadUTF();
    password = input->ReadUTF();

    delete input;
}
