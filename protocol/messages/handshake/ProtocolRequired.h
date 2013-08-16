#ifndef PROTOCOL_REQUIRED_H
#define PROTOCOL_REQUIRED_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class ProtocolRequired : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initProtocolRequired(unsigned int _requiredVersion, unsigned int _currentVersion);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 1;

		unsigned int requiredVersion;
		unsigned int currentVersion;
};

#endif // PROTOCOL_REQUIRED_H
