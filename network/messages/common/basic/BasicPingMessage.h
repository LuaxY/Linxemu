#ifndef BASIC_PING_MESSAGE_H
#define BASIC_PING_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../NetworkMessage.h"

class BasicPingMessage : public NetworkMessage
{
    public:
        //BasicPingMessage();
        NetworkMessage* getInstance() const;
        void initBasicPingMessage(bool _quiet);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 182;

        // variables of message
        bool quiet;

    private:
        bool _isInitialized;
};

#endif // BASIC_PING_MESSAGE_H
