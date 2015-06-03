#include "ConsoleLogEventHandler.h"

#include "LogManager.h"

#include <iostream>
#include <time.h>

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  ConsoleLogEventHandler()
* Description: Default constructor. Adds in 'm_types', LogEventType_ALL_LOG_EVENT
*						to listen to any kind of LogEvent, and
*						LogEventType_CONSOLE_LOG_EVENT because it is the console
*						Log Handler. Adds all possible levels inside the 'm_levels'
*						attribute.
* Inputs: none
**************************************************************************/
ConsoleLogEventHandler::ConsoleLogEventHandler()
{
    m_types.push_back(LogEventType::LogEventType_CONSOLE_LOG_EVENT);
    m_types.push_back(LogEventType::LogEventType_ALL_LOG_EVENT);

    m_levels.push_back(LogLevel::LogLevel_INFO);
    m_levels.push_back(LogLevel::LogLevel_WARN);
    m_levels.push_back(LogLevel::LogLevel_ERROR);

    m_levels.push_back(LogLevel::LogLevel_DEBUG);
}

/**************************************************************************
* Name:  ~ConsoleLogEventHandler()
* Description: Default destructor. Clears all attributes.
* Inputs: none
**************************************************************************/
ConsoleLogEventHandler::~ConsoleLogEventHandler()
{
    m_types.clear();
    m_levels.clear();
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name:  handleEvent(LogEvent& _event)
* Description: Method used to handle a LogEvent. Prints the log inside the console in std::cout.
* Inputs:
*				- _event : LogEvent&, Event to log inside the console.
* Returns: none
**************************************************************************/
void ConsoleLogEventHandler::handleEvent(LogEvent& _event)
{
    /* Useful to get the current time. */
    time_t current_time = time(0);
    tm* local_time = localtime(&current_time);

    /* Prints  the log in the console. */
    std::cout << std::to_string(local_time->tm_hour).c_str() << ":" << std::to_string(local_time->tm_min).c_str() << ":" << std::to_string(local_time->tm_sec).c_str() << " - " << _event;
}

/**************************************************************************
* Name:  closeHandler()
* Description: Method used to close the handler. Here, does nothing.
* Inputs: none
* Returns: none
**************************************************************************/
void ConsoleLogEventHandler::closeHandler()
{
}
