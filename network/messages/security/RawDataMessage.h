#ifndef RAW_DATA_MESSAGE_H
#define RAW_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../NetworkMessage.h"

class RawDataMessage : public NetworkMessage
{
    public:
        NetworkMessage* getInstance() const;
        void initRawDataMessage(unsigned short _length, char* _content);

        int getMessageId();
        bool isInitialized();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 6253;

        /******* VARIABLES LIST *******/
        unsigned short length;
        char* content;

    private:
        bool _isInitialized;
};

#endif // RAW_DATA_MESSAGE_H
