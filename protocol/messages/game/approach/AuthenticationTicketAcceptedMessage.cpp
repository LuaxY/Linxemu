#include "AuthenticationTicketAcceptedMessage.h"

INetworkMessage* AuthenticationTicketAcceptedMessage::getInstance() const
{
	return new AuthenticationTicketAcceptedMessage(*this);
}

void AuthenticationTicketAcceptedMessage::initAuthenticationTicketAcceptedMessage()
{
}

int AuthenticationTicketAcceptedMessage::getMessageId()
{
	return protocolId;
}

char* AuthenticationTicketAcceptedMessage::getMessageName()
{
	return "AuthenticationTicketAcceptedMessage";
}

void AuthenticationTicketAcceptedMessage::pack(MessageWriter *output)
{
}

void AuthenticationTicketAcceptedMessage::unpack(char *buffer)
{
}
