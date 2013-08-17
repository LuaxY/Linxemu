#ifndef BOOLEAN_BYTE_WRAPPER_H
#define BOOLEAN_BYTE_WRAPPER_H

class BooleanByteWrapper
{
private:
    int position;
    char* buffer;

public:
    static char SetFlag(char flag, char offset, bool value);
    static char SetFlag(int flag, char offset, bool value);
    static bool GetFlag(char flag, char offset);
};

#endif // BOOLEAN_BYTE_WRAPPER_H

