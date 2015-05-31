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

    public:
        static void pushEvent(LogEvent* _event);

        static void registerLogEventHandler(LogEventHandler* _handler);
        static void unregisterLogEventHandler(LogEventHandler* _handler);
        static bool pollEvents();

        static void showError(const char* _msg);

        static void print(std::string _str);

    private:
        static LogEvent* pollEvent(LogEvent* _event);

        static std::vector<LogEventHandler*> s_eventHandlers;
        static std::vector<LogEvent*> s_logEvents;
};

#endif
