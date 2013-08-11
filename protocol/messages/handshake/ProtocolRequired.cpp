#include "ProtocolRequired.h"

INetworkMessage* ProtocolRequired::getInstance() const
{
    return new ProtocolRequired(*this);
}

void ProtocolRequired::initProtocolRequired(unsigned int _requiredVersion, unsigned int _currentVersion)
{
	requiredVersion = _requiredVersion;
	currentVersion = _currentVersion;

	_isInitialized = true;
}

bool ProtocolRequired::isInitialized()
{
	return _isInitialized;
}

int ProtocolRequired::getMessageId()
{
	return protocolId;
}

char* ProtocolRequired::getMessageName()
{
	return "ProtocolRequired";
}

void ProtocolRequired::pack(MessageWriter *output)
{
	output->WriteUInt(requiredVersion);
	output->WriteUInt(currentVersion);
}

void ProtocolRequired::unpack(char *buffer)
{
    MessageReader *input = new MessageReader(buffer);

	requiredVersion = input->ReadUInt();
	currentVersion = input->ReadUInt();

	delete input;
}

void ProtocolRequired::reset()
{
	requiredVersion = 0;
	currentVersion = 0;

	_isInitialized = false;
}
