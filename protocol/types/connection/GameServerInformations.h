#ifndef GAME_SERVER_INFROMATIONS_H
#define GAME_SERVER_INFROMATIONS_H

#include "../../../utils/utils.h"
#include "../INetworkType.h"

class GameServerInformations : public INetworkType
{
public:
    void initGameServerInformations(unsigned short _id, char _status, char _completion, bool _isSelectable, char _charactersCount, long _date);

    int getTypeId();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 25;

    unsigned short id;
    char status;
    char completion;
    bool isSelectable;
    char charactersCount;
    long date;
};

#endif // GAME_SERVER_INFROMATIONS_H
