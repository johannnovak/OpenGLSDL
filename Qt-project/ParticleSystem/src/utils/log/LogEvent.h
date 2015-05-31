#ifndef LOGEVENT_H
#define LOGEVENT_H

#include <string>

enum LogEventType
{
    ConsoleLogEvent,
    QtLogEvent,
    AllLogEvent
};

enum LogLevel
{
    ERROR,
    WARN,
    DEBUG,
    INFO
};

class LogEvent
{
    protected:
        LogEventType m_type;
        std::string* m_content;
        LogLevel m_level;

    public:
        LogEvent();
        LogEvent(LogEventType _type);
        LogEvent(LogEventType _type, LogLevel _level, std::string _content);
        ~LogEvent();

        LogLevel getLevel();
        LogEventType getType() ;
        std::string getContent();

        bool operator==(const LogEvent& _event);

        friend std::ostream& operator<<(std::ostream& _o, LogEvent& _event);
};


#endif // LOGEVENT_H
