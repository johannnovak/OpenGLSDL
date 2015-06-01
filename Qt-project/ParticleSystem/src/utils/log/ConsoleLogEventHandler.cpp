#include "ConsoleLogEventHandler.h"

#include <iostream>
#include <time.h>
#include "LogManager.h"

ConsoleLogEventHandler::ConsoleLogEventHandler()
{
    m_masks.push_back(new LogEvent(LogEventType::ConsoleLogEvent));
    m_masks.push_back(new LogEvent(LogEventType::AllLogEvent));

    m_logLevels.push_back(LogLevel::INFO);
    m_logLevels.push_back(LogLevel::WARN);
    m_logLevels.push_back(LogLevel::ERROR);

    m_logLevels.push_back(LogLevel::DEBUG);
}

ConsoleLogEventHandler::~ConsoleLogEventHandler()
{
    m_masks.clear();
}

void ConsoleLogEventHandler::handleEvent(LogEvent& _event)
{
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    std::cout << std::to_string(localTime->tm_hour).c_str() << ":" << std::to_string(localTime->tm_min).c_str() << ":" << std::to_string(localTime->tm_sec).c_str() << " - " << _event;
}

std::vector<LogEvent*>& ConsoleLogEventHandler::getMasks()
{
    return m_masks;
}

void ConsoleLogEventHandler::closeHandler()
{
}
