#ifndef SELECTED_SERVER_DATA_MESSAGE_H
#define SELECTED_SERVER_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class SelectedServerDataMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initSelectedServerDataMessage(unsigned short _serverId, char* _address, unsigned short _port, bool _canCreateNewCharacter, char* _ticket);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 42;

		unsigned short serverId;
		char* address;
		unsigned short port;
		bool canCreateNewCharacter;
		char* ticket;
};

#endif // SELECTED_SERVER_DATA_MESSAGE_H
