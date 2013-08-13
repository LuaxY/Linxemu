#include "Frames.h"

void Frames::Register()
{
    addFrame(new AuthentificationFrame);
    addFrame(new LatencyFrame);
}

bool Frames::processMessage(INetworkMessage* message, Client* client)
{
    IFrame* tmp = 0;
    bool returnProcess = false;
    int i;

    for(i = 0; i < framesList.size(); i++)
    {
        tmp = framesList[i]->getInstance();;
        returnProcess = tmp->process(message, client);

        if(returnProcess)
            break;
    }

    return returnProcess;
}

void Frames::addFrame(IFrame* frame)
{
    framesList.push_back(frame);
}
