#include "Client.h"

Client::Client()
{
    socket = 0;
    phase = NEW_PACKET;
}
