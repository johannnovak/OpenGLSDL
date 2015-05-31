#ifndef CONSOLELOGEVENTHANDLER_H
#define CONSOLELOGEVENTHANDLER_H

#include "LogEventHandler.h"

class ConsoleLogEventHandler : public LogEventHandler
{
    public:
        ConsoleLogEventHandler();
        ~ConsoleLogEventHandler();

        bool handleEvent(LogEvent& _event);
        std::vector<LogEvent>& getMasks();
};

#endif // CONSOLELOGEVENTHANDLER_H
