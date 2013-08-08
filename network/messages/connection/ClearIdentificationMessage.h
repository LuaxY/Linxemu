#ifndef CLEAR_IDENTIFICATION_MESSAGE_H
#define CLEAR_IDENTIFICATION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../NetworkMessage.h"

class ClearIdentificationMessage : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        void initClearIdentificationMessage(char* _user, char* _password);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 888;

        /******* VARIABLES LIST *******/
        char* user;
        char* password;

    private:
        bool _isInitialized;
};

#endif // CLEAR_IDENTIFICATION_MESSAGE_H
