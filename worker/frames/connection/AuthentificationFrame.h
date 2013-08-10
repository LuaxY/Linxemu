#ifndef AUTHENTIFICATION_FRAME_H
#define AUTHENTIFICATION_FRAME_H

#include "../../../utils/utils.h"
#include "../IFrame.h"
#include <sqlite3.h>

class AuthentificationFrame : public IFrame
{
    public:
        IFrame* getInstance() const;
        char* getFrameName();
        bool process(INetworkMessage* message, Client* client);
};

#endif // AUTHENTIFICATION_FRAME_H
