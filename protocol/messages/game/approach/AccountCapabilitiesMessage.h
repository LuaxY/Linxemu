#ifndef ACCOUNT_CAPABILITIES_MESSAGE_H
#define ACCOUNT_CAPABILITIES_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class AccountCapabilitiesMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initAccountCapabilitiesMessage(unsigned int _accountId, bool _tutorialAvailable, unsigned short _breedsVisible, unsigned short _breedsAvailable, char _status);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 6216;

    unsigned int accountId;
    bool tutorialAvailable;
    unsigned short breedsVisible;
    unsigned short breedsAvailable;
    char status;
};

#endif // ACCOUNT_CAPABILITIES_MESSAGE_H
