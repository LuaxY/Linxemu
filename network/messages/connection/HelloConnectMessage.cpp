#include "HelloConnectMessage.h"

NetworkMessage* HelloConnectMessage::getInstance() const
{
    return new HelloConnectMessage(*this);
}

void HelloConnectMessage::initHelloConnectMessage(char* _salt, vector<int> _key)
{
	salt = _salt;
    key = _key;

	_isInitialized = true;
}

bool HelloConnectMessage::isInitialized()
{
	return _isInitialized;
}

int HelloConnectMessage::getMessageId()
{
	return protocolId;
}

void HelloConnectMessage::pack(MessageWriter *output)
{
	output->WriteUTF(salt);
	output->WriteUShort(key.size());
	for(int i = 0; i < key.size(); i++)
        output->WriteByte(key[i]);
}

void HelloConnectMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	salt = input->ReadUTF();
	unsigned short keyLen = input->ReadUShort();
	char byteKey = 0;

	for(int i = 0; i < keyLen; i++)
	{
        byteKey = input->ReadByte();
        key.push_back(byteKey);
	}

	delete input;
}

void HelloConnectMessage::reset()
{
	salt = NULL;
	key.clear();

	_isInitialized = false;
}
