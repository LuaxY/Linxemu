#ifndef BASIC_PING_MESSAGE_H
#define BASIC_PING_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../NetworkMessage.h"

class BasicPingMessage : public NetworkMessage
{
    public:
        BasicPingMessage();
        NetworkMessage* getInstance() const;
        void initBasicPingMessage(bool _quiet);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(MessageReader *input);
        void reset();

        static const int protocolId = 182;

    private:
        bool _isInitialized;

        bool quiet;
};

#endif // BASIC_PING_MESSAGE_H
