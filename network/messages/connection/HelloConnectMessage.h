#ifndef HELLO_CONNECT_MESSAGE_H
#define HELLO_CONNECT_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class HelloConnectMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        HelloConnectMessage(){};
        void initHelloConnectMessage(char* _salt, char* _key, int _keyLen);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 3;

        /******* VARIABLES LIST *******/
        char* salt;
        char* key;
        int keyLen;

    private:
        bool _isInitialized;
};

#endif // HELLO_CONNECT_MESSAGE_H
