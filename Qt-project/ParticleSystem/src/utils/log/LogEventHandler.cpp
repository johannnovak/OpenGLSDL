#include "LogEventHandler.h"


LogEventHandler::LogEventHandler()
{
}

LogEventHandler::~LogEventHandler()
{
}

bool LogEventHandler::canLog(LogLevel _level)
{
    std::vector<LogLevel>::iterator it = m_logLevels.begin();
    bool stop = false;
    while (!stop  && it != m_logLevels.end())
    {
        if(*it == _level)
            stop = true;
        ++it;
    }

    return stop;
}
