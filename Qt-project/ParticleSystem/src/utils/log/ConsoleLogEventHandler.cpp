#include "ConsoleLogEventHandler.h"

#include <iostream>

ConsoleLogEventHandler::ConsoleLogEventHandler()
{
    m_masks.push_back(LogEvent(LogEventType::ConsoleLogEvent));
}

ConsoleLogEventHandler::~ConsoleLogEventHandler()
{
}

bool ConsoleLogEventHandler::handleEvent(LogEvent& _event)
{
    if(_event.getLevel() == LogLevel::ERROR)
    {
        ++LogEventHandler::s_errorCount;

        if (LogEventHandler::s_errorCount > LOGMANAGER_ERROR_LIMIT)
        {
            std::cout << "Too many errors, program exiting\n\n" << std::endl;
            return true;
        }
    }

    std::cout << _event;
    return false;
}

std::vector<LogEvent>& ConsoleLogEventHandler::getMasks()
{
    return m_masks;
}
