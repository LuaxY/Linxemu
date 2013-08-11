#ifndef RAW_DATA_MESSAGE_H
#define RAW_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class RawDataMessage : public INetworkMessage
{
    public:
        INetworkMessage* getInstance() const;
        RawDataMessage(){};
        void initRawDataMessage(char* _content, unsigned short _length);

        int getMessageId();
        char* getMessageName();
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
