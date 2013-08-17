#ifndef AUTHENTICATION_TICKET_ACCEPTED_MESSAGE_H
#define AUTHENTICATION_TICKET_ACCEPTED_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class AuthenticationTicketAcceptedMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initAuthenticationTicketAcceptedMessage();

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 111;
};

#endif // AUTHENTICATION_TICKET_ACCEPTED_MESSAGE_H

