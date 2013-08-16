#ifndef AUTHENTICATION_TICKET_MESSAGE_H
#define AUTHENTICATION_TICKET_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class AuthenticationTicketMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initAuthenticationTicketMessage(char* _lang, char* _ticket);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 110;

		char* lang;
		char* ticket;
};

#endif // AUTHENTICATION_TICKET_MESSAGE_H
