#include "LatencyFrame.h"

IFrame* LatencyFrame::getInstance() const
{
    return new LatencyFrame(*this);
}

char* LatencyFrame::getFrameName()
{
    return "LatencyFrame";
}

bool LatencyFrame::process(INetworkMessage* message, Client* client)
{
    bool state = false;

    switch(message->getMessageId())
    {
    case 182:
        processMessage((BasicPingMessage*)message, client); // LatencyFrame
        state = true;
        break;
    }

    return state;
}

void LatencyFrame::processMessage(BasicPingMessage* message, Client* client)
{
    BasicPongMessage bpm;
    bpm.initBasicPongMessage(true);
    NetworkManager::sendTo(client->socket, bpm.getInstance());
}
