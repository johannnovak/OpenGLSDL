#include "LogManager.h"
#include <QDebug>
#include <string>

std::vector<LogEventHandler*> LogManager::s_eventHandlers;
std::vector<LogEvent*> LogManager::s_logEvents;

LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

void LogManager::pushEvent(LogEvent *_event)
{
    for(int i(0); i < LogManager::s_eventHandlers; ++i)
        for(int j(0); i < LogManager::s_eventHandlers[i]->getMasks().size(); ++j)
            if(LogManager::s_eventHandlers[i]->getMasks()[j] == *_event)
                LogManager::s_eventHandlers[i]->handleEvent(*event);
}

LogEvent* LogManager::pollEvent(LogEvent* _event)
{
    if(LogManager::s_logEvents.empty())
    {
        _event = nullptr;
    }
    else
    {
        _event = LogManager::s_logEvents.back();
        LogManager::s_logEvents.pop_back();
    }
    return _event;
}

void LogManager::registerLogEventHandler(LogEventHandler* _handler)
{
    if(_handler != NULL)
        LogManager::s_eventHandlers.push_back(_handler);
}

void LogManager::unregisterLogEventHandler(LogEventHandler* _handler)
{
    if(_handler == NULL)
        return;

    int size = LogManager::s_eventHandlers.size();
    for(int i = 0 ; i < size; ++i)
    {
        if(LogManager::s_eventHandlers[i] == _handler)
        {
            if(size == 1)
                LogManager::s_eventHandlers.clear();
            else
            {
                LogManager::s_eventHandlers[i] = LogManager::s_eventHandlers[size - 1];
                LogManager::s_eventHandlers.pop_back();
            }
            break;
        }
    }
}

bool LogManager::pollEvents()
{
    LogEvent* event = nullptr;
    while((event = pollEvent(event)))
    {
        for(int i(0); i < LogManager::s_eventHandlers.size(); ++i)
        {
            for(int j(0); i < LogManager::s_eventHandlers[i]->getMasks().size(); ++j)
            {
                if(LogManager::s_eventHandlers[i]->getMasks()[j] == *event)
                {
                    return LogManager::s_eventHandlers[i]->handleEvent(*event);
                }
            }
        }
    }
}
