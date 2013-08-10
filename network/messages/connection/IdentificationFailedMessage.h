#ifndef IDENTIFICATION_FAILED_MESSAGE_H
#define IDENTIFICATION_FAILED_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationFailedMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        IdentificationFailedMessage(){};
        IdentificationFailedMessage(IdentificationFailedMessage* message);
        void initIdentificationFailedMessage(char _reason);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 20;

        /******* VARIABLES LIST *******/
        char reason;

    private:
        bool _isInitialized;
};

#endif // IDENTIFICATION_FAILED_MESSAGE_H
