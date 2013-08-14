#ifndef SELECTED_SERVER_DATA_MESSAGE_H
#define SELECTED_SERVER_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"
#include "../../types/connection/GameServerInformations.h"
#include <vector>

class SelectedServerDataMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        SelectedServerDataMessage(){};
        SelectedServerDataMessage(SelectedServerDataMessage* message);
        void initSelectedServerDataMessage(unsigned short _serverId, char* _address, unsigned short _port, bool _canCreateNewCharacter, char* _ticket);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 42;

        /******* VARIABLES LIST *******/
        unsigned short serverId;
        char* address;
        unsigned short port;
        bool canCreateNewCharacter;
        char* ticket;

    private:
        bool _isInitialized;
};

#endif // SELECTED_SERVER_DATA_MESSAGE_H
