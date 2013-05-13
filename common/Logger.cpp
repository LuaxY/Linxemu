#include "Logger.h"

void Log(LOG_NAME logName, string message)
{
    switch(logName)
    {
        case DEBUG:
            cout << "[DEBUG] ";
            break;
        case ERROR:
            cout << "[ERROR] ";
            break;
        case INFO:
        default:
            cout << "[INFO] ";
            break;
    }

    cout << message << endl;
}
