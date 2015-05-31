#include "LogManager.h"
#include <QDebug>
#include <string>
#include "InputManager.h"

std::vector<LogEventHandler*> LogManager::s_eventHandlers;
unsigned int LogManager::s_errorCount = 0;

LogManager::LogManager()
{

}


LogManager::~LogManager()
{
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

void LogManager::pushEvent(LogEvent *_event)
{

    for(int i(0); i < LogManager::s_eventHandlers.size(); ++i)
        for(int j(0); j < LogManager::s_eventHandlers[i]->getMasks().size(); ++j)
            if(*LogManager::s_eventHandlers[i]->getMasks()[j] == *_event)
                if(LogManager::s_eventHandlers[i]->canLog(_event->getLevel()))
                    LogManager::s_eventHandlers[i]->handleEvent(*_event);

    if(_event->getLevel() == LogLevel::ERROR)
        ++LogManager::s_errorCount;
}

void LogManager::closeHandlers()
{
    for(int i(0); i < LogManager::s_eventHandlers.size(); ++i)
        LogManager::s_eventHandlers[i]->closeHandler();
}
