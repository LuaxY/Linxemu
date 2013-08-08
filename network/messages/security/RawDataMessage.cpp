#include "RawDataMessage.h"

NetworkMessage* RawDataMessage::getInstance() const
{
    return new RawDataMessage(*this);
}

void RawDataMessage::initRawDataMessage(char* _content, unsigned short _length)
{
	content = _content;
	length = _length;

	_isInitialized = true;
}

bool RawDataMessage::isInitialized()
{
	return _isInitialized;
}

int RawDataMessage::getMessageId()
{
	return protocolId;
}

char* RawDataMessage::getMessageName()
{
	return "RawDataMessage";
}

void RawDataMessage::pack(MessageWriter *output)
{
	output->WriteUShort(length);
	output->WriteBytes(content, length);
}

void RawDataMessage::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	length = input->ReadUShort();
	content = input->ReadBytes(length);

	delete input;
}

void RawDataMessage::reset()
{
	length = 0;
	content = NULL;

	_isInitialized = false;
}
