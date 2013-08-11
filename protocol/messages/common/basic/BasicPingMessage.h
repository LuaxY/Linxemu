#ifndef BASIC_PING_MESSAGE_H
#define BASIC_PING_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class BasicPingMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        BasicPingMessage(){};
        void initBasicPingMessage(bool _quiet);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 182;

        /******* VARIABLES LIST *******/
        bool quiet;

    private:
        bool _isInitialized;
};

#endif // BASIC_PING_MESSAGE_H
