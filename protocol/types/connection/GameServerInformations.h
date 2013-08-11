#ifndef GAME_SERVER_INFROMATIONS_H
#define GAME_SERVER_INFROMATIONS_H

#include "../../../utils/utils.h"
#include "../INetworkType.h"

class GameServerInformations : public INetworkType
{
    public:
        GameServerInformations(){};
        GameServerInformations(GameServerInformations* message);
        void initGameServerInformations(unsigned short _id, char _status, char _completion, bool _isSelectable, char _charactersCount, double _date);

        int getTypeId();
        void pack(MessageWriter *output);
        void unpack(char *buffer);
        void reset();

        static const int protocolId = 25;

        /******* VARIABLES LIST *******/
        unsigned short id;
        char status;
        char completion;
        bool isSelectable;
        char charactersCount;
        double date;
};

#endif // GAME_SERVER_INFROMATIONS_H
