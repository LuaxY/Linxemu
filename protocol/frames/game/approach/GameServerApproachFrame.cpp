#include "GameServerApproachFrame.h"

IFrame* GameServerApproachFrame::getInstance() const
{
    return new GameServerApproachFrame(*this);
}

char* GameServerApproachFrame::getFrameName()
{
	return "GameServerApproachFrame";
}

bool GameServerApproachFrame::process(INetworkMessage* message, Client* client)
{
    bool state = false;

    data = new MessageWriter();
    packet = new MessageWriter();

    switch(message->getMessageId())
    {
        case 110:
            processMessage((AuthenticationTicketMessage*)message, client);
            state = true;
            break;
    }

    delete data;
    delete packet;

    return state;
}

void GameServerApproachFrame::processMessage(AuthenticationTicketMessage* message, Client* client)
{
	cout << message->lang << " " << message->ticket << endl;

	AuthenticationTicketAcceptedMessage atacm;
	atacm.initAuthenticationTicketAcceptedMessage();
	atacm.pack(data);

	NetworkManager::writePacket(packet, atacm.getMessageId(), data->getBuffer(), data->getPosition());
	NetworkManager::sendTo(client->socket, packet->getBuffer(), packet->getPosition(), atacm.getInstance());
}
