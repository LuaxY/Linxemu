#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include "../../utils/utils.h"

template <class T> class Prototype
 {
    public:
        virtual ~Prototype(){}
        virtual T* getInstance() const = 0;
 };

class NetworkMessage : public Prototype<NetworkMessage>
{
    public:
        virtual int getMessageId() = 0;
        virtual bool isInitialized() = 0;
        virtual void pack(MessageWriter *output) = 0;
        virtual void unpack(MessageReader *input) = 0;
        virtual void reset() = 0;
};

#endif // NETWORK_MESSAGE_H
