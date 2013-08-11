#ifndef SERVER_STATUS_ENUM_H
#define SERVER_STATUS_ENUM_H

enum ServerStatusEnum
{
    STATUS_UNKNOWN = 0,
    OFFLINE = 1,
    STARTING = 2,
    ONLINE = 3,
    NOJOIN = 4,
    SAVING = 5,
    STOPING = 6,
    FULL = 7,
};

#endif // SERVER_STATUS_ENUM_H
