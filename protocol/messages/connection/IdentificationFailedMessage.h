#ifndef IDENTIFICATION_FAILED_MESSAGE_H
#define IDENTIFICATION_FAILED_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationFailedMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initIdentificationFailedMessage(char _reason);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 20;

		char reason;
};

#endif // IDENTIFICATIONFAILEDMESSAGE_H
