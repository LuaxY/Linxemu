#include "IdentificationSuccessMessage.h"

INetworkMessage* IdentificationSuccessMessage::getInstance() const
{
	return new IdentificationSuccessMessage(*this);
}

void IdentificationSuccessMessage::initIdentificationSuccessMessage(const char* _login, const char* _nickname, unsigned int _accountId, const char _communityId, bool _hasRights, const char* _secretQuestion, double _subscriptionEndDate, bool _wasAlreadyConnected, double _accountCreation)
{
	login = (char*)_login;
	nickname = (char*)_nickname;
	accountId = _accountId;
	communityId = _communityId;
	hasRights = _hasRights;
	secretQuestion = (char*)_secretQuestion;
	subscriptionEndDate = _subscriptionEndDate;
	wasAlreadyConnected = _wasAlreadyConnected;
	accountCreation = _accountCreation;
}

int IdentificationSuccessMessage::getMessageId()
{
	return protocolId;
}

char* IdentificationSuccessMessage::getMessageName()
{
	return "IdentificationSuccessMessage";
}

void IdentificationSuccessMessage::pack(MessageWriter *output)
{
	char box0 = 0;
	box0 = BooleanByteWrapper::SetFlag(box0, 0, hasRights);
	box0 = BooleanByteWrapper::SetFlag(box0, 1, wasAlreadyConnected);

	output->WriteByte(box0);
 	output->WriteUTF(login);
	output->WriteUTF(nickname);
	output->WriteUInt(accountId);
	output->WriteByte(communityId);
	output->WriteUTF(secretQuestion);
	output->WriteDouble(subscriptionEndDate);
	output->WriteDouble(accountCreation);
}

void IdentificationSuccessMessage::unpack(char *buffer)
{
}
