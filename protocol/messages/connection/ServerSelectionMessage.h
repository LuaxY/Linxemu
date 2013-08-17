#ifndef SERVER_SELECTION_MESSAGE_H
#define SERVER_SELECTION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class ServerSelectionMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initServerSelectionMessage(unsigned short _serverId);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 40;

    unsigned short serverId;
};

#endif // SERVER_SELECTION_MESSAGE_H
