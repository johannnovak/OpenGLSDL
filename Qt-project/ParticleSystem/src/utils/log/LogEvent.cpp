#include "LogEvent.h" // Implemented class.

#include <iostream>


///////////////////////////////////// PUBLIC //////////////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name: LogEvent()
* Description: Default constructor initializing a LogEvent.
* Inputs: none
**************************************************************************/
LogEvent::LogEvent()
{
    m_content = new std::string("");
}

/**************************************************************************
* Name: LogEvent(LogEventType _type)
* Description: Constructor initializing a LogEvent with only a _type. Only
*					used when registering LogEventHandlers.
* Inputs:
* 			- _type: LogEventType associated with this LogEvent.
**************************************************************************/
LogEvent::LogEvent(LogEventType _type):m_type(_type)
{
    m_content = new std::string("");
}

/**************************************************************************
* Name: LogEvent(LogEventType _type, LogLevel _level, std::string _content)
* Description: Constructor initializing a LogEvent with all its attributes.
*					Used when the user wants to log any kind of content.
* Inputs:
* 			- _type		: LogEventType associated with this LogEvent.
* 			- _level		: Level of priority of the log.
* 			- _content	: String content to write when handled.
**************************************************************************/
LogEvent::LogEvent(LogEventType _type, LogLevel _level, std::string _content):m_type(_type), m_level(_level)
{
    m_content = new std::string(_content);
}

/**************************************************************************
* Name: ~LogEvent()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
LogEvent::~LogEvent()
{
    if(m_content != NULL)
        delete m_content;
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: getLevel()
* Description: Getter for the 'm_level' attribute.
* Inputs: none
* Returns:
*			- m_level, LogLevel attribute.
**************************************************************************/
LogLevel LogEvent::getLevel()
{
    return m_level;
}

/**************************************************************************
* Name: getType()
* Description: Getter for the 'm_type' attribute.
* Inputs: none
* Returns:
*			- m_type, LogEventType attribute.
**************************************************************************/
LogEventType LogEvent::getType()
{
    return m_type;
}

/**************************************************************************
* Name: getContent()
* Description: Getter for the 'm_content' attribute.
* Inputs: none
* Returns:
*			- m_content, String attribute.
**************************************************************************/
std::string LogEvent::getContent()
{
    return *m_content;
}

//============================= OPERATORS ==============================================

/**************************************************************************
* Name: operator==()
* Description: Overloaded == operator of the class.
* Inputs:
*			- _event : LogEvent to test the equality with.
* Returns:
*			- True if the two events have the same LogEventType.
*			- False otherwise.
**************************************************************************/
bool LogEvent::operator==(const LogEvent& _event)
{
    return (m_type == _event.m_type);
}

/**************************************************************************
* Name: operator<<()
* Description: Overloaded << operator of the class.
* Inputs:
*			- _o 		: Outputstream where to stored the String representation
*							of the object.
*			- _event	: LogEvent to store in an ostream.
* Returns:
*			- _o : ostream containing the String representation of the object.
**************************************************************************/
std::ostream& operator<<(std::ostream& _o, LogEvent& _event)
{
    /* Adds the associated string of the priority level. */
    switch (_event.m_level)
    {
    case LogLevel::LogLevel_ERROR :
        _o << "ERROR : ";
        break;

    case LogLevel::LogLevel_WARN :
        _o << "WARN  : ";
        break;

    case LogLevel::LogLevel_DEBUG :
        _o << "DEBUG : ";
        break;

    case LogLevel::LogLevel_INFO :
        _o << "INFO  : ";
        break;

    default:
        _o << "XXXX  : ";
        break;
    }

    /* Stores the content inside the ostream. */
    _o << *_event.m_content << std::endl;

    return _o;
}
