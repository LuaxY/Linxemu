#ifndef IDENTIFICATION_SUCCESS_MESSAGE_H
#define IDENTIFICATION_SUCCESS_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationSuccessMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        IdentificationSuccessMessage(){};
        IdentificationSuccessMessage(IdentificationSuccessMessage* message);
        void initIdentificationSuccessMessage(const char* login, const char* nickname, unsigned int accountId, char communityId, bool hasRights, char* secretQuestion, long subscriptionEndDate, bool wasAlreadyConnected, long accountCreation);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 22;

        /******* VARIABLES LIST *******/
        char* login;
        char* nickname;
        unsigned int accountId;
        char communityId;
        bool hasRights;
        char* secretQuestion;
        long subscriptionEndDate;
        bool wasAlreadyConnected;
        long accountCreation;

    private:
        bool _isInitialized;
};

#endif // IDENTIFICATION_SUCCESS_MESSAGE_H
