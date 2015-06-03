#ifndef LOGEVENTHANDLER_H
#define LOGEVENTHANDLER_H

#define LOGMANAGER_ERROR_LIMIT 10

#include "LogEvent.h"

#include <vector>

/**************************************************************************
* Class: LogEventHandler
* Description: Abstract class designed to print logs. It has two properties :
*						it listens to any LogEventType registered in 'm_types' and
*						print only logs whose priority is contained in 'm_levels'.
*
**************************************************************************/
class LogEventHandler
{
/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:
         /* Vector of LogEventType defining which event to listen to. */
         std::vector<LogEventType> m_types;

         /* Vector of LogLevel defining which kind of LogEvent print. */
         std::vector<LogLevel> m_levels;

         /* Number of errors which havve occurred since the beginning. */
         static unsigned int s_errorCount;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  LogEventHandler()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        LogEventHandler();

        /**************************************************************************
        * Name:  LogEventHandler()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~LogEventHandler();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name:  getTypes()
        * Description: Getter for the 'm_types' attribute.
        * Inputs: none
        * Returns:
        *			- m_types : The LogEventType the Handler listens to.
        **************************************************************************/
        std::vector<LogEventType>& getTypes();

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
        bool canLogType(LogEventType _type);

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
        bool hasLogLevel(LogLevel _level);

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name:  handleEvent(LogEvent& _event)
        * Description: Abstract method used to handle a LogEvent and print it somewhere.
        * Inputs:
        *				- _event : LogEvent&, Event to log.
        * Returns: none
        **************************************************************************/
        virtual void handleEvent(LogEvent& _event) = 0;

        /**************************************************************************
        * Name:  closeHandler()
        * Description: Abstract method used to close the handler.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        virtual void closeHandler() = 0;
};

#endif // LOGEVENTHANDLER_H
