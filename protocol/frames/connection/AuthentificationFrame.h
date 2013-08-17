#ifndef AUTHENTIFICATION_FRAME_H
#define AUTHENTIFICATION_FRAME_H

#include "../../../utils/utils.h"
#include "../../../database/Database.h"
#include "../IFrame.h"
#include "../../enums/IdentificationFailureReasonEnum.h"
#include "../../enums/ServerStatusEnum.h"
#include "../../enums/ServerConnectionErrorEnum.h"

#include <vector>

class AuthentificationFrame : public IFrame
{
public:
    IFrame* getInstance() const;
    char* getFrameName();
    bool process(INetworkMessage* message, Client* client);

private:
    MessageWriter *data;
    MessageWriter *packet;

    void processMessage(IdentificationMessage* message, Client* client);
    void processMessage(ClearIdentificationMessage* message, Client* client);
    void processMessage(ServerSelectionMessage* message, Client* client);
};

#endif // AUTHENTIFICATION_FRAME_H
