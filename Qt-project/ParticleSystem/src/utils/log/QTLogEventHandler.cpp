#include "QTLogEventHandler.h" // Implemented Class.

#include <QScrollBar>
#include <sstream>
#include <time.h>

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  ConsoleLogEventHandler()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
QTLogEventHandler::QTLogEventHandler()
{
    m_types.push_back(LogEventType::LogEventType_QT_LOG_EVENT);
    m_types.push_back(LogEventType::LogEventType_ALL_LOG_EVENT);

    m_levels.push_back(LogLevel::LogLevel_INFO);
    m_levels.push_back(LogLevel::LogLevel_WARN);
    m_levels.push_back(LogLevel::LogLevel_ERROR);

    //    m_levels.push_back(LogLevel::LogLevel_DEBUG);

    m_frontTag = "<font color='%1'>";
    m_errorColor = "#FF0000";
    m_warnColor = "#FF9933";
    m_debugColor = "#33CC33";
    m_infoColor = "#0000FF";
    m_defaultColor = "#000000";
    m_backTag = "</font>";

    resize(350,750);
    setWindowTitle(trUtf8("LogWindow"));
    QPlainTextEdit::setReadOnly(true);
    show();
}

/**************************************************************************
* Name:  ~ConsoleLogEventHandler()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
QTLogEventHandler::~QTLogEventHandler()
{
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name:  handleEvent(LogEvent& _event)
* Description: Method used to handle a LogEvent. Prints the log inside the console in std::cout.
* Inputs:
*				- _event : LogEvent&, Event to log inside the console.
* Returns: none
**************************************************************************/
void QTLogEventHandler::handleEvent(LogEvent& _event)
{
    QString log;

    switch(_event.getLevel())
    {
    case LogLevel::LogLevel_ERROR:
        log += m_frontTag.arg(m_errorColor);
        break;

    case LogLevel::LogLevel_WARN:
        log += m_frontTag.arg(m_warnColor);
        break;

    case LogLevel::LogLevel_DEBUG:
        log += m_frontTag.arg(m_debugColor);
        break;

    case LogLevel::LogLevel_INFO:
        log += m_frontTag.arg(m_infoColor);
        break;

    default:
        log += m_frontTag.arg(m_defaultColor);
        break;
    }

    std::ostringstream event_string_stream;
    event_string_stream << _event;
    time_t current_time = time(0);
    tm* local_time = localtime(&current_time);
    log += std::to_string(local_time->tm_hour).c_str();
    log += ":";
    log += std::to_string(local_time->tm_min).c_str();
    log += ":";
    log += std::to_string(local_time->tm_sec).c_str();
    log += " - ";
    log += event_string_stream.rdbuf()->str().c_str() + m_backTag;
    appendHtml(log);

    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

/**************************************************************************
* Name:  closeHandler()
* Description: Method used to close the handler. Here, does nothing.
* Inputs: none
* Returns: none
**************************************************************************/
void QTLogEventHandler::closeHandler()
{
    close();
}
