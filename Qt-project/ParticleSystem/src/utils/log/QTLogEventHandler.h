#ifndef QTLOGEVENTHANDLER_H
#define QTLOGEVENTHANDLER_H

#include "LogEventHandler.h"
#include "QPlainTextEdit"

/**************************************************************************
* Class: QTLogEventHandler
* Description: Class inheriting LogEventHandler. It is designed to print logs
*						inside a QPlainTextEdit set as readnoly(true).
*
**************************************************************************/
class QTLogEventHandler : public LogEventHandler, QPlainTextEdit
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* HTML "<font " tag. */
        QString m_frontTag;

        /* HTML red color. */
        QString m_errorColor;

        /* HTML yellow color. */
        QString m_warnColor;

        /* HTML green color. */
        QString m_debugColor;

        /* HTML blue color. */
        QString m_infoColor;

        /* HTML black color. */
        QString m_defaultColor;

        /* HTML "</font>" tag. */
        QString m_backTag;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  QTLogEventHandler()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        QTLogEventHandler();

        /**************************************************************************
        * Name:  ~QTLogEventHandler()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        ~QTLogEventHandler();

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

#endif // QTLOGEVENTHANDLER_H
