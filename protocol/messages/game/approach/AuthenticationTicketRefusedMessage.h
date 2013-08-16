#ifndef AUTHENTICATION_TICKET_REFUSED_MESSAGE_H
#define AUTHENTICATION_TICKET_REFUSED_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class AuthenticationTicketRefusedMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initAuthenticationTicketRefusedMessage();

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 112;
};

#endif // AUTHENTICATION_TICKET_REFUSED_MESSAGE_H

