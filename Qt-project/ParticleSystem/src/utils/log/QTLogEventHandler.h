#ifndef QTLOGEVENTHANDLER_H
#define QTLOGEVENTHANDLER_H

#include "LogEventHandler.h"
#include "QPlainTextEdit"

class QTLogEventHandler : public LogEventHandler, QPlainTextEdit
{
    public:
        QTLogEventHandler();
        ~QTLogEventHandler();

        void handleEvent(LogEvent& _event);
        std::vector<LogEvent*>& getMasks();
        void closeHandler();

    private:
        QString m_frontTag;
        QString m_errorColor;
        QString m_warnColor;
        QString m_debugColor;
        QString m_infoColor;
        QString m_defaultColor;
        QString m_backTag;
};

#endif // QTLOGEVENTHANDLER_H
