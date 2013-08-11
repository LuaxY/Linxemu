#ifndef FRAMES_H
#define FRAMES_H

#include <vector>

#include "../utils/utils.h"
#include "../network/NetworkManager.h"
#include "../network//MessageReceiver.h"
#include "../protocol/messages/INetworkMessage.h"
#include "../protocol/frames/IFrame.h"
#include "../protocol/frames/framesList.h"

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
