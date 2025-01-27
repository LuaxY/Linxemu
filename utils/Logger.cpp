#include "Logger.h"

bool Logger::isDebugLogEnabled()
{
    return debugLog;
}

void Logger::Log(LOG_NAME logName, string location, string message, bool newLine)
{
    if(logName == DEBUG && !debugLog)
        return;

    switch(logName)
    {
    case DEBUG:
        cout << "[\033[1;36mDEBUG\033[0m] ";
        break;
    case ERROR:
        cout << "[\033[1;31mERROR\033[0m] ";
        break;
    case WORKER:
        cout << "[\033[1;32mWORKER\033[0m] ";
        break;
    case INFO:
    default:
        cout << "[\033[1;33mINFO\033[0m] ";
        break;
    }

    if(timeLog)
        cout << "[" << Logger::getCurrentTime() << "] ";

    if(logName == ERROR)
        cout << "[" << location << "] ";

    cout << message;

    if(newLine)
        cout << endl;
}

string Logger::getCurrentTime()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    string currentTime;
    stringstream tmp;

    tmp << now->tm_hour << ':'
        << now->tm_min << ':'
        << now->tm_sec;

    currentTime = tmp.str();

    return currentTime;
}
