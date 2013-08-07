#ifndef RAW_DATA_MESSAGE_H
#define RAW_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../NetworkMessage.h"

class RawDataMessage : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        void initRawDataMessage(char* _content, unsigned short _length);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 6253;

        /******* VARIABLES LIST *******/
        char* content;
        unsigned short length;

    private:
        bool _isInitialized;
};

#endif // RAW_DATA_MESSAGE_H
