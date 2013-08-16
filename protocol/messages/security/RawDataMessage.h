#ifndef RAW_DATA_MESSAGE_H
#define RAW_DATA_MESSAGE_H

#include "../../../utils/utils.h"
#include "../INetworkMessage.h"

class RawDataMessage : public INetworkMessage
{
	public:
		INetworkMessage* getInstance() const;
		void initRawDataMessage(char* _content, unsigned short _length);

		int getMessageId();
		char* getMessageName();
		void pack(MessageWriter *output);
		void unpack(char *buffer);

		static const int protocolId = 6253;

		char* content;
		unsigned short length;
};

#endif // RAW_DATA_MESSAGE_H
