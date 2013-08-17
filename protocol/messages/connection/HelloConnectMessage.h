#ifndef HELLO_CONNECT_MESSAGE_H
#define HELLO_CONNECT_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class HelloConnectMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initHelloConnectMessage(char* _salt, char* _key, unsigned short _length);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 3;

    char* salt;
    char* key;
    unsigned short length;
};

#endif // HELLO_CONNECT_MESSAGE_H
