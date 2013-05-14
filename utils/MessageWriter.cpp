#include "MessageWriter.h"

MessageWriter::MessageWriter(): position(0)
{
    buffer = new char[256];
}

MessageWriter::MessageWriter(int len): position(0)
{
    buffer = new char[len];
}

MessageWriter::~MessageWriter()
{
    delete[] buffer;
}

int MessageWriter::getPosition()
{
    return position;
}

char* MessageWriter::getBuffer()
{
    return buffer;
}

unsigned short MessageWriter::SwapUShort(unsigned short s)
{
    return (s >> 8) | (s << 8);
}

unsigned int MessageWriter::SwapUInt(unsigned int i)
{
    return (i >> 24) | ((i << 8) & 0x00FF0000) | ((i >> 8) & 0x0000FF00) | (i << 24);
}

unsigned long MessageWriter::SwapULong(unsigned long l)
{
    return (l >> 56) | ((l << 40) & 0x00FF000000000000) | ((l << 24) & 0x0000FF0000000000) | ((l << 8) & 0x000000FF00000000) | ((l >> 8) & 0x00000000FF000000) | ((l >> 24) & 0x0000000000FF0000) | ((l >> 40) & 0x000000000000FF00) | (l << 56);
}

void MessageWriter::WriteShort(short s)
{
    s = SwapUShort(s);
    memcpy(buffer + position, &s, sizeof(s));
    position += 2;
}

void MessageWriter::WriteUShort(unsigned short s)
{
    s = SwapUShort(s);
    memcpy(buffer + position, &s, sizeof(s));
    position += 2;
}

void MessageWriter::WriteByte(char b)
{
    buffer[position] = b;
    position++;
}

void MessageWriter::WriteBytes(char* bs, int len)
{
    int i;

    for(i = 0; i < len; i++)
        buffer[position + i] = bs[i];

    position += i;
}

void MessageWriter::WriteInt(int i)
{
    i = SwapUInt(i);
    memcpy(buffer + position, &i, sizeof(i));
    position += 4;
}

void MessageWriter::WriteUInt(unsigned int i)
{
    i = SwapUInt(i);
    memcpy(buffer + position, &i, sizeof(i));
    position += 4;
}

void MessageWriter::WriteUTF(char* str)
{
    int i;
    int len = strlen(str);

    WriteShort((unsigned short)len);

    for(i = 0; i < len; i++)
        buffer[position + i] = str[i];

    position += i;
}

void MessageWriter::WriteBool(bool b)
{
    if(b)
        WriteByte(1);
    else
        WriteByte(0);
}
