#ifndef SERVER_SELECTION_MESSAGE_H
#define SERVER_SELECTION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class ServerSelectionMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        ServerSelectionMessage(){};
        ServerSelectionMessage(ServerSelectionMessage* message);
        void initServerSelectionMessage(unsigned short _serverId);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 40;

        /******* VARIABLES LIST *******/
        unsigned short serverId;

    private:
        bool _isInitialized;
};

#endif // SERVER_SELECTION_MESSAGE_H
