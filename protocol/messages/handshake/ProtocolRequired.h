#ifndef PROTOCOL_REQUIRED_H
#define PROTOCOL_REQUIRED_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class ProtocolRequired : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        ProtocolRequired(){};
        void initProtocolRequired(unsigned int _requiredVersion, unsigned int _currentVersion);

        int getMessageId();
        char* getMessageName();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 1;

        /******* VARIABLES LIST *******/
        unsigned int requiredVersion;
        unsigned int currentVersion;

    private:
        bool _isInitialized;
};

#endif // PROTOCOL_REQUIRED_H
