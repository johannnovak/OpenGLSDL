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

        virtual bool handleEvent(LogEvent& _event) = 0;
        virtual std::vector<LogEvent>& getMasks() = 0;

        static unsigned int s_errorCount;
    protected:
        std::vector<LogEvent> m_masks;
};

#endif // LOGEVENTHANDLER_H
