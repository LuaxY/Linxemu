#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

using namespace std;

enum LOG_NAME
{
    DEBUG,
    INFO,
    ERROR
};

void Log(LOG_NAME logName, string message);

#endif // LOGGER_H
