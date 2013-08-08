#include "ClearIdentificationMessage.h"

NetworkMessage* ClearIdentificationMessage::getInstance() const
{
    return new ClearIdentificationMessage(*this);
}

ClearIdentificationMessage::ClearIdentificationMessage(ClearIdentificationMessage* message)
{
    user = message->user;
    password = message->password;
}

void ClearIdentificationMessage::initClearIdentificationMessage(char* _user, char* _password)
{
    user = _user;
    password = _password;

	_isInitialized = true;
}

bool ClearIdentificationMessage::isInitialized()
{
	return _isInitialized;
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

void ClearIdentificationMessage::reset()
{
	user = NULL;
	password = NULL;

	_isInitialized = false;
}
