#include "Client.h"

Client::Client()
{
    /*fd_set rdfs;

    FD_ZERO(&rdfs);
    FD_SET(socket, &rdfs);
    FD_SET(phase, &rdfs);*/
    socket = 0;
    phase = NEW_PACKET;
}
