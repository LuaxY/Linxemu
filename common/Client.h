#ifndef CLIENT_H
#define CLIENT_H

#include <queue>
#include <sys/select.h>

using namespace std;

typedef int SOCKET;
enum State { NEW_PACKET, HEADER_OK, LENGTH_OK };

class Client
{
    public:
        Client();

        SOCKET socket;
        State phase;

        queue<char> bufferQueue;
        unsigned short lastMessageId;
        unsigned short lastMessageLengthType;
        unsigned short lastMessageLength;

        char* salt;
};

#endif // CLIENT_H
