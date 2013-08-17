#ifndef SERVERS_LIST_MESSAGE_H
#define SERVERS_LIST_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"
#include "../../types/connection/GameServerInformations.h"
#include <vector>

class ServersListMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initServersListMessage(vector<GameServerInformations*> _servers);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 30;

    vector<GameServerInformations*> servers;
};

#endif // SERVERS_LIST_MESSAGE_H
