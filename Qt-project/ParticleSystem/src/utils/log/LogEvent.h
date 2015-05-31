#ifndef LOGEVENT_H
#define LOGEVENT_H

#include <string>

enum LogEventType
{
    ConsoleLogEvent,
    QtLogEvent
};

enum LogLevel
{
    ERROR,
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
        LogEvent(LogEventType _type, std::string _content, LogLevel _level);
        ~LogEvent();

        LogLevel getLevel();
        LogEventType getType() ;
        std::string getContent();

        bool operator==(const LogEvent& _event);

        friend std::ostream& operator<<(std::ostream& _o, LogEvent& _event);
};


#endif // LOGEVENT_H
