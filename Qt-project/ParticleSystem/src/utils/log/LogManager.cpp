#include "LogManager.h"
#include <QDebug>
#include <string>
#include "InputManager.h"

std::vector<LogEventHandler*> LogManager::s_eventHandlers;
unsigned int LogManager::s_errorCount = 0;

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE ======================================

/**************************************************************************
* Name:  LogManager()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
LogManager::LogManager()
{
}

/**************************************************************************
* Name:  ~LogManager()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
LogManager::~LogManager()
{
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: registerLogEventHandler(LogEventHandler* _handler)
* Description: Adds a LogEventHandler inside the 's_eventHandlers' attribute.
* Inputs:
*				- _handler : LogEventHandler*, handler to register in the LogManager.
* Returns: none
**************************************************************************/
void LogManager::registerLogEventHandler(LogEventHandler* _handler)
{
    if(_handler != nullptr)
        LogManager::s_eventHandlers.push_back(_handler);
}

/**************************************************************************
* Name: pushEvent(LogEventType _type, LogLevel _level, std::string _content)
* Description: Pushes a LogEvent to all of thee LogHandlers registered only
*						if they cna log such LogEventType and if they has the
*						appropriate priority.
* Inputs:
*				- _type		: LogEventType, specifies the LogEventType in which it
*									has to be logged.
*				- _level  	: LogLevel, priority of the log.
*				- _content	: std::string, Content of the log to be printed.
* Returns: none
**************************************************************************/
void LogManager::pushEvent(LogEventType _type, LogLevel _level, std::string _content)
{
    LogEvent event(_type, _level, _content);

    for(uint32 i(0); i < LogManager::s_eventHandlers.size(); ++i)
        if(LogManager::s_eventHandlers[i]->canLogType(_type))
            if(LogManager::s_eventHandlers[i]->hasLogLevel(_level))
                LogManager::s_eventHandlers[i]->handleEvent(event);

    if(event.getLevel() == LogLevel::LogLevel_ERROR)
        ++LogManager::s_errorCount;
}

/**************************************************************************
* Name: closeHandlers()
* Description: Close all registered handlers.
* Inputs: none
* Returns: none
**************************************************************************/
void LogManager::closeHandlers()
{
    for(uint32 i(0); i < LogManager::s_eventHandlers.size(); ++i)
        LogManager::s_eventHandlers[i]->closeHandler();
}

/**************************************************************************
* Name: unregisterLogEventHandler(LogEventHandler* _handler)
* Description: Removes one LogEventHandler from the 's_eventHandlers' attribute.
* Inputs:
*				- _handler : LogEventHandler*, handler to unregister in the LogManager.
* Returns: none
**************************************************************************/
void LogManager::unregisterLogEventHandler(LogEventHandler* _handler)
{
    if (_handler == nullptr)
        return;

    int size = LogManager::s_eventHandlers.size();
    for (uint32 i = size-1 ; i > -1; --i)
    {
        if (i = size - 1)
        {
            delete LogManager::s_eventHandlers[i];
            LogManager::s_eventHandlers.pop_back();
            if(LogManager::s_eventHandlers.empty())
                LogManager::s_eventHandlers.clear();
        }
        else if (LogManager::s_eventHandlers[i] == _handler)
        {
            delete LogManager::s_eventHandlers[i];
            for (int j(i); j < size - 2; ++j)
                LogManager::s_eventHandlers[i] = LogManager::s_eventHandlers[i+1];
            LogManager::s_eventHandlers.resize((size-1)*sizeof(LogEventHandler*));
        }
    }
}

/**************************************************************************
* Name: unregisterAllLogEventHandler()
* Description: Removes all LogEventHandlers from the 's_eventHandlers' attribute.
* Inputs: none
* Returns: none
**************************************************************************/
void LogManager::unregisterAllLogEventHandler()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Unregistering all LogEventHandlers...");
    std::vector<LogEventHandler*>::iterator it = LogManager::s_eventHandlers.begin();
    while (it != LogManager::s_eventHandlers.end())
    {
        delete *it;
        ++it;
    }
    LogManager::s_eventHandlers.clear();

    std::cout << "Unregistering successful." << std::endl;
}
