#ifndef FRAMES_H
#define FRAMES_H

#include <vector>

#include "../../utils/utils.h"

#include "../../network/managers/NetworkManager.h"
#include "../../network/managers/MessageReceiver.h"

#include "../../network/messages/INetworkMessage.h"
#include "../frames/IFrame.h"

using namespace std;

class Frames
{
    vector<IFrame*> framesList;
    void addFrame();
    void removeFrame();

    void processMessage(INetworkMessage* message);
};

#endif // FRAMES_H
