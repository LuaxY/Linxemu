#ifndef BASIC_PONG_MESSAGE_H
#define BASIC_PONG_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../NetworkMessage.h"

class BasicPongMessage : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        BasicPongMessage(){};
        void initBasicPongMessage(bool _quiet);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 183;

        /******* VARIABLES LIST *******/
        bool quiet;

    private:
        bool _isInitialized;
};

#endif // BASIC_PONG_MESSAGE_H

