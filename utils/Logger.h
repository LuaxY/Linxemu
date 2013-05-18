#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

enum LOG_NAME
{
    DEBUG,
    INFO,
    ERROR,
    THREAD
};

class Logger
{
    public:
        static void Log(LOG_NAME logName, string message, bool newLine = true);
        static bool isDebugLogEnabled();

    private:
        static string getCurrentTime();
        static const bool debugLog = true;
        static const bool timeLog = true;
};

#endif // LOGGER_H
