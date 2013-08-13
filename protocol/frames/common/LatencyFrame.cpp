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

    data = new MessageWriter();
    packet = new MessageWriter();

    switch(message->getMessageId())
    {
        case 182:
            processMessage((BasicPingMessage*)message, client); // LatencyFrame
            state = true;
            break;
    }

    delete data;
    delete packet;

    return state;
}

void LatencyFrame::processMessage(BasicPingMessage* message, Client* client)
{
    BasicPongMessage bpm;
    bpm.initBasicPongMessage(true);
    bpm.pack(data);

    NetworkManager::writePacket(packet, bpm.getMessageId(), data->getBuffer(), data->getPosition());
    NetworkManager::sendTo(client->sock, packet->getBuffer(), packet->getPosition(), bpm.getInstance());
}
