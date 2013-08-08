#include "HelloConnectMessage.h"

NetworkMessage* HelloConnectMessage::getInstance() const
{
    return new HelloConnectMessage(*this);
}

void HelloConnectMessage::initHelloConnectMessage(char* _salt, char* _key, int _keyLen)
{
    salt = _salt;
    key = _key;
    keyLen = _keyLen;

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

char* HelloConnectMessage::getMessageName()
{
	return "HelloConnectMessage";
}

void HelloConnectMessage::pack(MessageWriter *output)
{
	output->WriteUTF(salt);
    output->WriteUShort(keyLen);
    for(int i = 0; i < keyLen; i++)
        output->WriteByte(key[i]);
}

void HelloConnectMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	salt = input->ReadUTF();
	unsigned short keyLen = input->ReadUShort();
	char byteKey = 0;

	for(int i = 0; i < keyLen; i++)
        key[i] =  input->ReadByte();

	delete input;
}

void HelloConnectMessage::reset()
{
	salt = NULL;
	key = NULL;

	_isInitialized = false;
}
