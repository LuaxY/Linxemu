#ifndef SELECTED_SERVER_REFUSED_MESSAGE_H
#define SELECTED_SERVER_REFUSED_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class SelectedServerRefusedMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initSelectedServerRefusedMessage(unsigned short _serverId, char _error, char _serverStatus);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 41;

		unsigned short serverId;
		char error;
		char serverStatus;
};

#endif // SELECTED_SERVER_REFUSED_MESSAGE_H
