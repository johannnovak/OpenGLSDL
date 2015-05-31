#include "LogEvent.h"

#include <iostream>

LogEvent::LogEvent()
{
    m_content = new std::string("");
}

LogEvent::LogEvent(LogEventType _type):m_type(_type)
{
    m_content = new std::string("");
}

LogEvent::LogEvent(LogEventType _type, std::string _content, LogLevel _level):m_type(_type), m_level(_level)
{
    m_content = new std::string(_content);
}

LogEvent::~LogEvent()
{
    if(m_content != NULL)
        delete m_content;
}

LogLevel LogEvent::getLevel()
{
    return m_level;
}

LogEventType LogEvent::getType()
{
    return m_type;
}

std::string LogEvent::getContent()
{
    return *m_content;
}

bool LogEvent::operator==(const LogEvent& _event)
{
    return (m_type == _event.m_type);
}


std::ostream& operator<<(std::ostream& _o, LogEvent& _event)
{
    switch(_event.m_level)
    {
        case LogLevel::ERROR :
            _o << "ERROR : ";
            break;

        case LogLevel::DEBUG :
            _o << "DEBUG : ";
            break;

        case LogLevel::INFO :
            _o << "INFO  : ";
            break;

        default:
            _o << "XXXX  : ";
            break;
    }

    _o << *_event.m_content << std::endl;

    return _o;
}
