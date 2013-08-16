#ifndef CLEAR_IDENTIFICATION_MESSAGE_H
#define CLEAR_IDENTIFICATION_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class ClearIdentificationMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initClearIdentificationMessage(char* _user, char* _password);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 888;

		char* user;
		char* password;
};

#endif // CLEAR_IDENTIFICATION_MESSAGE_H
