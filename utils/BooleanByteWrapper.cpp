#include "BooleanByteWrapper.h"

char BooleanByteWrapper::SetFlag(char flag, char offset, bool value)
{
    /*if (offset >= 8)
        throw new ArgumentException("offset must be lesser than 8");*/

    return value ? (char)(flag | (1 << offset)) : (char)(flag & 255 - (1 << offset));
}

char BooleanByteWrapper::SetFlag(int flag, char offset, bool value)
{
    /*if (offset >= 8)
        throw new ArgumentException("offset must be lesser than 8");*/

    return value ? (char)(flag | (1 << offset)) : (char)(flag & 255 - (1 << offset));
}

bool BooleanByteWrapper::GetFlag(char flag, char offset)
{
    /*if (offset >= 8)
        throw new ArgumentException("offset must be lesser than 8");*/

    return (flag & (char)(1 << offset)) != 0;
}
