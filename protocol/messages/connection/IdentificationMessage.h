#ifndef IDENTIFICATION_MESSAGE_H
#define IDENTIFICATION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        IdentificationMessage(){};
        IdentificationMessage(IdentificationMessage* message);
        void initIdentificationMessage();

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 4;

        /******* VARIABLES LIST *******/


    private:
        bool _isInitialized;
};

#endif // IDENTIFICATION_MESSAGE_H
