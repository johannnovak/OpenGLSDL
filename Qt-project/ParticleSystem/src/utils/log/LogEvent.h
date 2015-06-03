#ifndef __LOGEVENT_H__
#define __LOGEVENT_H__

#include "Types.h"

#include <string>

/**************************************************************************
* Enum: LogEventType
* Description: Enum which registers all types of LogEvent that can occur.
**************************************************************************/
enum LogEventType
{
    LogEventType_CONSOLE_LOG_EVENT = 0, 	// LogEvent aimed at being output in the console.
    LogEventType_QT_LOG_EVENT,      			// LogEvent aimed at being output in a QtPlainTextEdit.
    LogEventType_ALL_LOG_EVENT      			// LogEvent aimed at being output in all registered Handlers.
};

/**************************************************************************
* Enum: LogLevel
* Description: Enum which registers all kind of Level the LogManager can
*              handle.
**************************************************************************/
enum LogLevel
{
    LogLevel_ERROR = 0,	// Level used when an error occured.
    LogLevel_WARN,  		// Level used when something is not alright but that is not lethal to the program.
    LogLevel_DEBUG, 		// Level used for debugging the program.
    LogLevel_INFO   		// Level used to inform the user.
};


/**************************************************************************
* Class: LogEvent
* Description: Class designed to store the content of a log. It is
* 						associated with a LogLevel specifying the priority
* 						of the log and to an EventType telling where to log
* 						the content.
**************************************************************************/
class LogEvent
{
/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:

        /* LogEventType associated with the Log requested. */
        LogEventType m_type;

        /* Content to print. */
        std::string* m_content;

        /* Level of priority of the log. */
        LogLevel m_level;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================
        /**************************************************************************
        * Name: LogEvent()
        * Description: Default constructor initializing a LogEvent.
        * Inputs: none
        **************************************************************************/
        LogEvent();

        /**************************************************************************
        * Name: LogEvent(LogEventType _type)
        * Description: Constructor initializing a LogEvent with only a _type. Only
        *					used when registering LogEventHandlers.
        * Inputs:
        * 			- _type: LogEventType associated with this LogEvent.
        **************************************************************************/
        LogEvent(LogEventType _type);

        /**************************************************************************
        * Name: LogEvent(LogEventType _type, LogLevel _level, std::string _content)
        * Description: Constructor initializing a LogEvent with all its attributes.
        *					Used when the user wants to log any kind of content.
        * Inputs:
        * 			- _type		: LogEventType associated with this LogEvent.
        * 			- _level		: Level of priority of the log.
        * 			- _content	: String content to write when handled.
        **************************************************************************/
        LogEvent(LogEventType _type, LogLevel _level, std::string _content);

        /**************************************************************************
        * Name: ~LogEvent()
        * Description: Default Destructor.
        * Inputs: none
        **************************************************************************/
        ~LogEvent();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: getLevel()
        * Description: Getter for the 'm_level' attribute.
        * Inputs: none
        * Returns:
        *			- m_level, LogLevel attribute.
        **************************************************************************/
        LogLevel getLevel();

        /**************************************************************************
        * Name: getType()
        * Description: Getter for the 'm_type' attribute.
        * Inputs: none
        * Returns:
        *			- m_type, LogEventType attribute.
        **************************************************************************/
        LogEventType getType() ;

        /**************************************************************************
        * Name: getContent()
        * Description: Getter for the 'm_content' attribute.
        * Inputs: none
        * Returns:
        *			- m_content, String attribute.
        **************************************************************************/
        std::string getContent();

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
        bool operator==(const LogEvent& _event);

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
        friend std::ostream& operator<<(std::ostream& _o, LogEvent& _event);
};


#endif // __LOGEVENT_H__
