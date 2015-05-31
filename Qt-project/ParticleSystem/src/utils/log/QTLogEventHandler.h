#ifndef QTLOGEVENTHANDLER_H
#define QTLOGEVENTHANDLER_H

#include "LogEventHandler.h"
#include "QWidget"

class QTLogEventHandler : public LogEventHandler, QWidget
{
    public:
        QTLogEventHandler();
        ~QTLogEventHandler();

        bool handleEvent(LogEvent& _event);
        std::vector<LogEvent>& getMasks();

};

#endif // QTLOGEVENTHANDLER_H
