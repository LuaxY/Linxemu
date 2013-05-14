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

class Logger
{
    public:
        static void Log(LOG_NAME logName, string message, bool newLine = true);
        static bool isDebugLogEnabled();

    private:
        static const bool debugLog = true;
};

#endif // LOGGER_H
