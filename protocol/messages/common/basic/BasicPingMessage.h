#ifndef BASIC_PING_MESSAGE_H
#define BASIC_PING_MESSAGE_H

#include "../../../../utils/utils.h"
#include "../../INetworkMessage.h"

class BasicPingMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initBasicPingMessage(bool _quiet);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 182;

		bool quiet;
};

#endif // BASIC_PING_MESSAGE_H
