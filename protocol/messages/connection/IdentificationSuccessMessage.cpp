#include "IdentificationSuccessMessage.h"

INetworkMessage* IdentificationSuccessMessage::getInstance() const
{
    return new IdentificationSuccessMessage(*this);
}

IdentificationSuccessMessage::IdentificationSuccessMessage(IdentificationSuccessMessage* message)
{
    login = message->login;
    nickname = message->nickname;
    accountId = message->accountId;
    communityId = message->communityId;
    hasRights = message->hasRights;
    secretQuestion = message->secretQuestion;
    subscriptionEndDate = message->subscriptionEndDate;
    wasAlreadyConnected = message->wasAlreadyConnected;
    accountCreation = message->accountCreation;
}

void IdentificationSuccessMessage::initIdentificationSuccessMessage(const char* _login, const char* _nickname, unsigned int _accountId, char _communityId, bool _hasRights, char* _secretQuestion, long _subscriptionEndDate, bool _wasAlreadyConnected, long _accountCreation)
{
    login = (char*)_login;
    nickname = (char*)_nickname;
    accountId = _accountId;
    communityId = _communityId;
    hasRights = _hasRights;
    secretQuestion = _secretQuestion;
    subscriptionEndDate = _subscriptionEndDate;
    wasAlreadyConnected = _wasAlreadyConnected;
    accountCreation = _accountCreation;

	_isInitialized = true;
}

bool IdentificationSuccessMessage::isInitialized()
{
	return _isInitialized;
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
    output->WriteULong(subscriptionEndDate);
    output->WriteULong(accountCreation);
}

void IdentificationSuccessMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	delete input;
}

void IdentificationSuccessMessage::reset()
{
	login = NULL;
    nickname = NULL;
    accountId = 0;
    communityId = 0;
    hasRights = false;
    secretQuestion = NULL;
    subscriptionEndDate = 0;
    wasAlreadyConnected = false;
    accountCreation = false;

	_isInitialized = false;
}
