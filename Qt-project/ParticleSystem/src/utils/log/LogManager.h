#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "LogEventHandler.h"
#include "LogEvent.h"

#include <iostream>
#include <string>
#include <vector>

/**************************************************************************
* Class: LogManager
* Description: Static Class designed to first register LogEventHandler.
*					Then, the user will only have to push log Events that will
*					be handled by these handlers.
*
**************************************************************************/
class LogManager
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* Vector of Handler to which the LogEvent are pushed. */
        static std::vector<LogEventHandler*> s_eventHandlers;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:

        /* Number of errors which have occured since the beginning of the program. */
        static unsigned int s_errorCount;

    //============================= LIFECYCLE ======================================

        /**************************************************************************
        * Name:  LogManager()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        LogManager();

        /**************************************************************************
        * Name:  ~LogManager()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~LogManager();

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: registerLogEventHandler(LogEventHandler* _handler)
        * Description: Adds a LogEventHandler inside the 's_eventHandlers' attribute.
        * Inputs:
        *				- _handler : LogEventHandler*, handler to register in the LogManager.
        * Returns: none
        **************************************************************************/
        static void registerLogEventHandler(LogEventHandler* _handler);

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
        static void pushEvent(LogEventType _type, LogLevel _level, std::string _content);

        /**************************************************************************
        * Name: closeHandlers()
        * Description: Close all registered handlers.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        static void closeHandlers();

        /**************************************************************************
        * Name: unregisterLogEventHandler(LogEventHandler* _handler)
        * Description: Removes one LogEventHandler from the 's_eventHandlers' attribute.
        * Inputs:
        *				- _handler : LogEventHandler*, handler to unregister in the LogManager.
        * Returns: none
        **************************************************************************/
        static void unregisterLogEventHandler(LogEventHandler* _handler);

        /**************************************************************************
        * Name: unregisterAllLogEventHandler()
        * Description: Removes all LogEventHandlers from the 's_eventHandlers' attribute.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        static void unregisterAllLogEventHandler();


};

#endif
