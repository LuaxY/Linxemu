#include "AuthenticationTicketMessage.h"

INetworkMessage* AuthenticationTicketMessage::getInstance() const
{
	return new AuthenticationTicketMessage(*this);
}

void AuthenticationTicketMessage::initAuthenticationTicketMessage(char* _lang, char* _ticket)
{
	lang = _lang;
	ticket = _ticket;
}

int AuthenticationTicketMessage::getMessageId()
{
	return protocolId;
}

char* AuthenticationTicketMessage::getMessageName()
{
	return "AuthenticationTicketMessage";
}

void AuthenticationTicketMessage::pack(MessageWriter *output)
{
	output->WriteUTF(lang);
	output->WriteUTF(ticket);
}

void AuthenticationTicketMessage::unpack(char *buffer)
{
	MessageReader *input = new MessageReader(buffer);

	lang = input->ReadUTF();
	ticket = input->ReadUTF();

	delete input;
}
