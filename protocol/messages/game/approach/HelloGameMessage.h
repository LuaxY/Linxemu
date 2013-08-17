#ifndef HELLO_GAME_MESSAGE_H
#define HELLO_GAME_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class HelloGameMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initHelloGameMessage();

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 101;
};

#endif // HELLO_GAME_MESSAGE_H

