#ifndef HELLO_CONNECT_MESSAGE_H
#define HELLO_CONNECT_MESSAGE_H

#include <vector>

#include "../../../utils/utils.h"
#include "../NetworkMessage.h"

class HelloConnectMessage : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        void initHelloConnectMessage(char* _salt, vector<int> _key);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 3;

        /******* VARIABLES LIST *******/
        char* salt;
        vector<int> key;

    private:
        bool _isInitialized;
};

#endif // HELLO_CONNECT_MESSAGE_H
