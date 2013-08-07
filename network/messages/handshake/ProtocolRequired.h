#ifndef PROTOCOL_REQUIRED_H
#define PROTOCOL_REQUIRED_H

#include "../../../utils/utils.h"
#include "../NetworkMessage.h"

class ProtocolRequired : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        void initProtocolRequired(unsigned int _requiredVersion, unsigned int _currentVersion);

        int getMessageId();
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
