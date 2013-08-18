#ifndef GAME_SERVER_APPROACH_FRAME_H
#define GAME_SERVER_APPROACH_FRAME_H

#include "../../../../utils/utils.h"
#include "../../../../database/Database.h"
#include "../../IFrame.h"
#include "../../../types/game/character/choice/CharacterBaseInformations.h"
#include "../../../types/game/look/EntityLook.h"

class GameServerApproachFrame : public IFrame
{
public:
    IFrame* getInstance() const;
    char* getFrameName();
    bool process(INetworkMessage* message, Client* client);

private:
    MessageWriter *data;
    MessageWriter *packet;

    void processMessage(AuthenticationTicketMessage* message, Client* client);
    void processMessage(CharactersListRequestMessage* message, Client* client);
};

#endif // GAME_SERVER_APPROACH_FRAME_H

