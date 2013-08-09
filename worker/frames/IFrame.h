#ifndef IFRAME_H
#define IFRAME_H

#include <map>

#include "../../utils/utils.h"
#include "../../network/managers/NetworkManager.h"
#include "../../network/managers/MessageReceiver.h"
#include "../../network/messages/INetworkMessage.h"

using namespace std;

template <class T> class PrototypeFrame
 {
    public:
        virtual ~PrototypeFrame(){}
        virtual T* getInstance() const = 0;
 };

class IFrame : public PrototypeFrame<IFrame>
{
    public:
        virtual char* getFrameName() = 0;
        virtual bool process(INetworkMessage* message, Client* client) = 0;
};

#endif // IFRAME_H

