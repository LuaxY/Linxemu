#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <map>

#include "../../utils/utils.h"

using namespace std;

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
        virtual void unpack(char *buffer) = 0;
        virtual void reset() = 0;
};

#endif // NETWORK_MESSAGE_H
