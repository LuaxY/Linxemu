#include "Logger.h"

bool Logger::isDebugLogEnabled()
{
    return debugLog;
}

void Logger::Log(LOG_NAME logName, string message, bool newLine)
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
        case INFO:
        default:
            cout << "[\033[1;33mINFO\033[0m] ";
            break;
    }

    cout << message;

    if(newLine)
        cout << endl;
}
