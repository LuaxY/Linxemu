#ifndef FRAMES_H
#define FRAMES_H

#include <vector>

#include "../../utils/utils.h"
#include "../../network/managers/NetworkManager.h"
#include "../../network/managers/MessageReceiver.h"
#include "../../network/messages/INetworkMessage.h"
#include "../frames/IFrame.h"
#include "../frames/framesList.h"

using namespace std;

class Frames
{
    public:
        void Register();
        bool processMessage(INetworkMessage* message, Client* client);

    private:
        vector<IFrame*> framesList;
        void addFrame(IFrame* frame);
        //void removeFrame();

};

#endif // FRAMES_H
