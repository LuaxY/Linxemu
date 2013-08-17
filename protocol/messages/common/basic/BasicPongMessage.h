#ifndef BASIC_PONG_MESSAGE_H
#define BASIC_PONG_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class BasicPongMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initBasicPongMessage(bool _quiet);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 183;

    bool quiet;
};

#endif // BASIC_PONG_MESSAGE_H
