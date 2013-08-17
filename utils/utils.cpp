#include "utils.h"

static const char salt_rand[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

static const char token_rand[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

char* genSalt(int len)
{
    srand(time(NULL));
    char* salt = new char[len];
    for(int i = 0; i < len; ++i)
        salt[i] = salt_rand[rand() % (sizeof(salt_rand) - 1)];
    salt[len] = 0;
    return salt;
}

char* genToken(int len)
{
    srand(time(NULL));
    char* salt = new char[len];
    for(int i = 0; i < len; ++i)
        salt[i] = token_rand[rand() % (sizeof(token_rand) - 1)];
    salt[len] = 0;
    return salt;
}
