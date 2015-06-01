#include "QTLogEventHandler.h"

#include <QScrollBar>
#include <sstream>
#include <time.h>

QTLogEventHandler::QTLogEventHandler()
{
    m_masks.push_back(new LogEvent(LogEventType::QtLogEvent));
    m_masks.push_back(new LogEvent(LogEventType::AllLogEvent));

    m_logLevels.push_back(LogLevel::INFO);
    m_logLevels.push_back(LogLevel::WARN);
    m_logLevels.push_back(LogLevel::ERROR);

//    m_logLevels.push_back(LogLevel::DEBUG);

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

QTLogEventHandler::~QTLogEventHandler()
{
}

void QTLogEventHandler::handleEvent(LogEvent& _event)
{
    QString log;

    switch(_event.getLevel())
    {
        case LogLevel::ERROR:
            log += m_frontTag.arg(m_errorColor);
            break;

        case LogLevel::WARN:
            log += m_frontTag.arg(m_warnColor);
            break;

        case LogLevel::DEBUG:
            log += m_frontTag.arg(m_debugColor);
            break;

        case LogLevel::INFO:
            log += m_frontTag.arg(m_infoColor);
            break;

        default:
            log += m_frontTag.arg(m_defaultColor);
            break;
    }

    std::ostringstream eventStringStream;
    eventStringStream << _event;
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    log += std::to_string(localTime->tm_hour).c_str();
    log += ":";
    log += std::to_string(localTime->tm_min).c_str();
    log += ":";
    log += std::to_string(localTime->tm_sec).c_str();
    log += " - ";
    log += eventStringStream.rdbuf()->str().c_str() + m_backTag;
    appendHtml(log);

    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

std::vector<LogEvent*>& QTLogEventHandler::getMasks()
{
    return m_masks;
}

void QTLogEventHandler::closeHandler()
{
    close();
}
