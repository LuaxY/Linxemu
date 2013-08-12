#ifndef AUTHENTIFICATION_FRAME_H
#define AUTHENTIFICATION_FRAME_H

#include "../../../utils/utils.h"
#include "../../../database/mysql++.h"
#include "../IFrame.h"
#include "../../enums/IdentificationFailureReasonEnum.h"
#include "../../enums/ServerStatusEnum.h"

#include <vector>

class AuthentificationFrame : public IFrame
{
    public:
        IFrame* getInstance() const;
        char* getFrameName();
        bool process(INetworkMessage* message, Client* client);
};

#endif // AUTHENTIFICATION_FRAME_H
