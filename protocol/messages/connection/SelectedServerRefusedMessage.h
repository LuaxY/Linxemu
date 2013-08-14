#ifndef SELECTED_SERVER_REFUSED_MESSAGE_H
#define SELECTED_SERVER_REFUSED_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"
#include "../../types/connection/GameServerInformations.h"
#include <vector>

class SelectedServerRefusedMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        SelectedServerRefusedMessage(){};
        SelectedServerRefusedMessage(SelectedServerRefusedMessage* message);
        void initSelectedServerRefusedMessage(unsigned short _serverId, char _error, char _serverStatus);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 41;

        /******* VARIABLES LIST *******/
        unsigned short serverId;
        char error;
        char serverStatus;

    private:
        bool _isInitialized;
};

#endif // SELECTED_SERVER_REFUSED_MESSAGE_H
