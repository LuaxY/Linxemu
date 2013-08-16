#ifndef IDENTIFICATION_MESSAGE_H
#define IDENTIFICATION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class IdentificationMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initIdentificationMessage();

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 4;

};

#endif // IDENTIFICATION_MESSAGE_H
