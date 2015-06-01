#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "LogEventHandler.h"
#include "LogEvent.h"

class LogManager
{

    public:
        LogManager();
        virtual ~LogManager();

        static void closeHandlers();

        static unsigned int s_errorCount;
    public:
        static void registerLogEventHandler(LogEventHandler* _handler);
        static void unregisterLogEventHandler(LogEventHandler* _handler);

        static void pushEvent(LogEvent* _event);

    private:
        static std::vector<LogEventHandler*> s_eventHandlers;
};

#endif
