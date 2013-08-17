#ifndef SERVER_SETTINGS_MESSAGE_H
#define SERVER_SETTINGS_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class ServerSettingsMessage : public INetworkMessage
{
public:
    INetworkMessage* getInstance() const;
    void initServerSettingsMessage(char* _lang, char _community, char _gameType);

    int getMessageId();
    char* getMessageName();
    void pack(MessageWriter *output);
    void unpack(char *buffer);

    static const int protocolId = 6340;

    char* lang;
    char community;
    char gameType;
};

#endif // SERVER_SETTINGS_MESSAGE_H
