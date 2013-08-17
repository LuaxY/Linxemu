#ifndef IDENTIFICATION_SUCCESS_MESSAGE_H
#define IDENTIFICATION_SUCCESS_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationSuccessMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initIdentificationSuccessMessage(const char* _login, const char* _nickname, unsigned int _accountId, char _communityId, bool _hasRights, const char* _secretQuestion, double _subscriptionEndDate, bool _wasAlreadyConnected, double _accountCreation);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 22;

    char* login;
    char* nickname;
    unsigned int accountId;
    char communityId;
    bool hasRights;
    char* secretQuestion;
    double subscriptionEndDate;
    bool wasAlreadyConnected;
    double accountCreation;
};

#endif // IDENTIFICATION_SUCCESS_MESSAGE_H
