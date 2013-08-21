#ifndef LATENCY_FRAME_H
#define LATENCY_FRAME_H

#include "../../../utils/utils.h"
#include "../../../database/Database.h"
#include "../IFrame.h"

class LatencyFrame : public IFrame
{
public:
    IFrame* getInstance() const;
    char* getFrameName();
    bool process(INetworkMessage* message, Client* client);

private:
    void processMessage(BasicPingMessage* message, Client* client);
};

#endif // LATENCY_FRAME_H
