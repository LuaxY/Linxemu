#include "AuthenticationTicketRefusedMessage.h"

INetworkMessage* AuthenticationTicketRefusedMessage::getInstance() const
{
	return new AuthenticationTicketRefusedMessage(*this);
}

void AuthenticationTicketRefusedMessage::initAuthenticationTicketRefusedMessage()
{
}

int AuthenticationTicketRefusedMessage::getMessageId()
{
	return protocolId;
}

char* AuthenticationTicketRefusedMessage::getMessageName()
{
	return "AuthenticationTicketRefusedMessage";
}

void AuthenticationTicketRefusedMessage::pack(MessageWriter *output)
{
}

void AuthenticationTicketRefusedMessage::unpack(char *buffer)
{
}
