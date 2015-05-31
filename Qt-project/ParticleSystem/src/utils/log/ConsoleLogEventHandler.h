#ifndef CONSOLELOGEVENTHANDLER_H
#define CONSOLELOGEVENTHANDLER_H

#include "LogEventHandler.h"

class ConsoleLogEventHandler : public LogEventHandler
{
    public:
        ConsoleLogEventHandler();
        ~ConsoleLogEventHandler();

        void handleEvent(LogEvent& _event);
        std::vector<LogEvent*>& getMasks();
        void closeHandler();
};

#endif // CONSOLELOGEVENTHANDLER_H
