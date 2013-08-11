#ifndef SERVER_LIST_MESSAGE_H
#define SERVER_LIST_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"
#include "../../types/connection/GameServerInformations.h"
#include <vector>

class ServersListMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        ServersListMessage(){};
        ServersListMessage(ServersListMessage* message);
        void initServersListMessage(vector<GameServerInformations*> _servers);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 30;

        /******* VARIABLES LIST *******/
        vector<GameServerInformations*> servers;

    private:
        bool _isInitialized;
};

#endif // SERVER_LIST_MESSAGE_H
