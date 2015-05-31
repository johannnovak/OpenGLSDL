#ifndef LOGEVENTHANDLER_H
#define LOGEVENTHANDLER_H

#define LOGMANAGER_ERROR_LIMIT 10

#include <vector>
#include "LogEvent.h"

class LogEventHandler
{
    public:
        LogEventHandler();
        virtual ~LogEventHandler();

        virtual void handleEvent(LogEvent& _event) = 0;
        virtual std::vector<LogEvent*>& getMasks() = 0;
        bool canLog(LogLevel _level);
        virtual void closeHandler() = 0;

        static unsigned int s_errorCount;
    protected:
        std::vector<LogEvent*> m_masks;
        std::vector<LogLevel> m_logLevels;
};

#endif // LOGEVENTHANDLER_H
