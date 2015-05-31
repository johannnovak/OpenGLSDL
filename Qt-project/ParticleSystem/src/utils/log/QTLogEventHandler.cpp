#include "QTLogEventHandler.h"

QTLogEventHandler::QTLogEventHandler()
{
}

QTLogEventHandler::~QTLogEventHandler()
{
}

bool QTLogEventHandler::handleEvent(LogEvent& _event)
{

}

std::vector<LogEvent>& QTLogEventHandler::getMasks()
{
    return m_masks;
}
