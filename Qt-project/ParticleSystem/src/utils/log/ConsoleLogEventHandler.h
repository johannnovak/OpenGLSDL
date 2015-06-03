#ifndef __CONSOLELOGEVENTHANDLER_H__
#define __CONSOLELOGEVENTHANDLER_H__

#include "LogEventHandler.h"

/**************************************************************************
* Class: ConsoleLogEventHandler
* Description: Class inheriting LogEventHandler. It is designed to print logs
*						inside the console as std::cout.
*
**************************************************************************/
class ConsoleLogEventHandler : public LogEventHandler
{
/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  ConsoleLogEventHandler()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        ConsoleLogEventHandler();

        /**************************************************************************
        * Name:  ~ConsoleLogEventHandler()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        ~ConsoleLogEventHandler();

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name:  handleEvent(LogEvent& _event)
        * Description: Method used to handle a LogEvent. Prints the log inside the console in std::cout.
        * Inputs:
        *				- _event : LogEvent&, Event to log inside the console.
        * Returns: none
        **************************************************************************/
        void handleEvent(LogEvent& _event);

        /**************************************************************************
        * Name:  closeHandler()
        * Description: Method used to close the handler. Here, does nothing.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        void closeHandler();
};

#endif // __CONSOLELOGEVENTHANDLER_H__
