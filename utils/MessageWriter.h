#ifndef MESSAGE_WRITER_H
#define MESSAGE_WRITER_H

#include <cstring>

class MessageWriter
{
private:
    int position;
    char* buffer;

public:
    MessageWriter();
    MessageWriter(int);
    ~MessageWriter();

    int     getPosition();
    char*   getBuffer();

    unsigned short  SwapUShort(unsigned short);
    unsigned int    SwapUInt(unsigned int);
    unsigned long   SwapULong(unsigned long);

    void WriteShort(short);
    void WriteUShort(unsigned short);
    void WriteByte(char);
    void WriteBytes(char*, int);
    void WriteInt(int);
    void WriteUInt(unsigned int);
    void WriteUTF(char*);
    void WriteBool(bool);
};

#endif // MESSAGE_WRITER_H

