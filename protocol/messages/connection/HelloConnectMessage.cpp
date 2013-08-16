#include "HelloConnectMessage.h"

INetworkMessage* HelloConnectMessage::getInstance() const
{
	return new HelloConnectMessage(*this);
}

void HelloConnectMessage::initHelloConnectMessage(char* _salt, char* _key, unsigned short _length)
{
	salt = _salt;
	key = _key;
	length = _length;
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
	output->WriteUShort(length);
    for(int i = 0; i < length; i++)
        output->WriteByte(key[i]);
}

void HelloConnectMessage::unpack(char *buffer)
{
	MessageReader *input = new MessageReader(buffer);

	salt = input->ReadUTF();
	length = input->ReadUShort();
	key = new char[length];
	for(int i = 0; i < length; i++)
        key[i] =  input->ReadByte();

	delete input;
}
