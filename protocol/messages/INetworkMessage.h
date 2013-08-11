#ifndef INETWORK_MESSAGE_H
#define INETWORK_MESSAGE_H

#include <map>

#include "../../utils/utils.h"

using namespace std;

template <class T> class PrototypeNet
 {
    public:
        virtual ~PrototypeNet(){}
        virtual T* getInstance() const = 0;
 };

class INetworkMessage : public PrototypeNet<INetworkMessage>
{
    public:
        virtual int getMessageId() = 0;
        virtual char* getMessageName() = 0;
        virtual bool isInitialized() = 0;
        virtual void pack(MessageWriter *output) = 0;
        virtual void unpack(char *buffer) = 0;
        virtual void reset() = 0;
};

#endif // INETWORK_MESSAGE_H
