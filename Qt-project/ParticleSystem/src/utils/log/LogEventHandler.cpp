#include "LogEventHandler.h"


/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  LogEventHandler()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
LogEventHandler::LogEventHandler()
{
}

/**************************************************************************
* Name:  LogEventHandler()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
LogEventHandler::~LogEventHandler()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name:  getTypes()
* Description: Getter for the 'm_types' attribute.
* Inputs: none
* Returns:
*			- m_types : The LogEventType the Handler listens to.
**************************************************************************/
std::vector<LogEventType>& LogEventHandler::getTypes()
{
    return m_types;
}

//============================= INQUIRY =====================================

/**************************************************************************
* Name: canLogType(LogEventType _type)
* Description: Tells if the LogEventHandler can log such LogEventType.
* Inputs:
*			- _type : LogEventType, type to test if it is contained in the
*							handler's 'm_types' attribute.
* Returns:
*			- True if the Handler can log such LogEventType.
*			- False otherwise.
**************************************************************************/
bool LogEventHandler::canLogType(LogEventType _type)
{
    std::vector<LogEventType>::iterator it = m_types.begin();
    bool stop = false;
    while (!stop  && it != m_types.end())
    {
        if(*it == _type)
            stop = true;
        ++it;
    }

    return stop;
}

/**************************************************************************
* Name: hasLogLevel(LogLevel _level)
* Description: Tells if the LogEventHandler has the priority to log such level.
* Inputs:
*			- _level : LogLevel, level to test if it is contained in the
*							handler's 'm_levels' attribute.
* Returns:
*			- True if the Handler has such LogLevel.
*			- False otherwise.
**************************************************************************/
bool LogEventHandler::hasLogLevel(LogLevel _level)
{
    std::vector<LogLevel>::iterator it = m_levels.begin();
    bool stop = false;
    while (!stop  && it != m_levels.end())
    {
        if(*it == _level)
            stop = true;
        ++it;
    }

    return stop;
}
