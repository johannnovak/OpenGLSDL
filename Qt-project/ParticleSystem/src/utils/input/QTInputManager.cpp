#include "QTInputManager.h"

#include <iostream>

bool QTInputManager::eventFilter(QObject* _object, QEvent* _event)
{
    if(_event->type() == QEvent::KeyPress)
    {
        QKeyEvent* qKeyEvent = (QKeyEvent*) _event;
        keyPressEvent(qKeyEvent);
        return true;
    }
    else if(_event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* qKeyEvent = (QKeyEvent*) _event;
        keyReleaseEvent(qKeyEvent);
        return true;
    }
    else if(_event->type() == QEvent::MouseMove)
    {
        QMouseEvent* qMouseEvent = (QMouseEvent*) _event;
        mouseMoveEvent(qMouseEvent);
        return true;
    }
    else if(_event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* qMouseEvent = (QMouseEvent*) _event;
        mousePressEvent(qMouseEvent);
        return true;
    }
    else if(_event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* qMouseEvent = (QMouseEvent*) _event;
        mouseReleaseEvent(qMouseEvent);
        return true;
    }
    else
    {
        return QObject::eventFilter(_object,_event);
    }
}

QTInputManager::QTInputManager()
{
	m_keyPressed = new bool[IM_KEY_LAST];
	m_mouseButtonPressed = new bool[IM_MOUSE_LAST];

	for (unsigned int i = 0; i < IM_KEY_LAST; ++i)
	{
		m_keyPressed[i] = false;
	}
	
	for (unsigned int i = 0; i < IM_MOUSE_LAST; ++i)
	{
		m_mouseButtonPressed[i] = false;
	}

    m_eventMasks.push_back(QKeyEvent::KeyPress);
    m_eventMasks.push_back(QKeyEvent::KeyRelease);
    m_eventMasks.push_back(QMouseEvent::MouseButtonPress);
    m_eventMasks.push_back(QMouseEvent::MouseButtonRelease);
    m_eventMasks.push_back(QMouseEvent::MouseMove);

    m_mouseMotion.x = 0;
    m_mouseMotion.y = 0;
    m_mouseMotion.dx = 0;
    m_mouseMotion.dy = 0;
}

QTInputManager::~QTInputManager()
{
	delete[] m_keyPressed;
	delete[] m_mouseButtonPressed;
}

void QTInputManager::initialize()
{
    s_instance = new QTInputManager();
}

bool QTInputManager::isKeyDown(KeyId _keyId)
{
	if (_keyId < IM_KEY_LAST)
		return m_keyPressed[_keyId];

	return false;
}

bool QTInputManager::isKeyUp(KeyId _keyId)
{
	if (_keyId < IM_KEY_LAST)
		return !m_keyPressed[_keyId];

	return false;
}

bool QTInputManager::isMouseButtonDown(MouseButtonId _mouseId)
{
	if (_mouseId < IM_MOUSE_LAST)
		return m_mouseButtonPressed[_mouseId];

	return false;
}

bool QTInputManager::isMouseButtonUp(MouseButtonId _mouseId)
{
	if (_mouseId < IM_MOUSE_LAST)
		return !m_mouseButtonPressed[_mouseId];

	return false;
}

MouseMotion& QTInputManager::getMouseMotion()
{
	return m_mouseMotion;
}

void QTInputManager::resetMouseMotion()
{
	m_mouseMotion.dx = 0;
	m_mouseMotion.dy = 0;
}

void QTInputManager::mousePressEvent( QMouseEvent*_event )
{
    QMouseEvent* qtMouseEvent = (QMouseEvent*) _event;
    MouseButtonId mouseButtonId = QTMouseEventToMouseButtonId(qtMouseEvent);

    m_mouseButtonPressed[mouseButtonId] = true;
}

void QTInputManager::mouseReleaseEvent( QMouseEvent*_event )
{
    QMouseEvent* qtMouseEvent = (QMouseEvent*) _event;
    MouseButtonId mouseButtonId = QTMouseEventToMouseButtonId(qtMouseEvent);

    m_mouseButtonPressed[mouseButtonId] = false;
}

void QTInputManager::mouseMoveEvent( QMouseEvent* _event )
{
    QMouseEvent* qtMouseEvent = (QMouseEvent*) _event;

    m_mouseMotion.x = qtMouseEvent->x();
    m_mouseMotion.y = qtMouseEvent->y();
    m_mouseMotion.dx = qtMouseEvent->x() - m_mouseMotion.dx;
    m_mouseMotion.dy = qtMouseEvent->y() - m_mouseMotion.dy;
}

void QTInputManager::keyPressEvent( QKeyEvent* _event )
{
    QKeyEvent* qtKeyEvent = (QKeyEvent*) _event;
    KeyId keyId = QTKeyEventToKeyId(qtKeyEvent);

    m_keyPressed[keyId] = true;
}

void QTInputManager::keyReleaseEvent( QKeyEvent* _event )
{
    QKeyEvent* qtKeyEvent = (QKeyEvent*) _event;
    KeyId keyId = QTKeyEventToKeyId(qtKeyEvent);

    m_keyPressed[keyId] = false;
}

std::vector<QEvent>& QTInputManager::getMasks()
{
	return m_eventMasks;
}

KeyId QTInputManager::QTKeyEventToKeyId(QKeyEvent* _event)
{
    switch (_event->key())
	{
    case Qt::Key_0:
		return IM_KEY_0;
    case Qt::Key_1:
		return IM_KEY_1;
    case Qt::Key_2:
        return IM_KEY_2;
    case Qt::Key_3:
        return IM_KEY_3;
    case Qt::Key_4:
        return IM_KEY_4;
    case Qt::Key_5:
        return IM_KEY_5;
    case Qt::Key_6:
        return IM_KEY_6;
    case Qt::Key_7:
        return IM_KEY_7;
    case Qt::Key_8:
        return IM_KEY_8;
    case Qt::Key_9:
        return IM_KEY_9;

    case Qt::Key_A:
        return IM_KEY_A;
    case Qt::Key_B:
        return IM_KEY_B;
    case Qt::Key_C:
        return IM_KEY_C;
    case Qt::Key_D:
        return IM_KEY_D;
    case Qt::Key_E:
        return IM_KEY_E;
    case Qt::Key_F:
        return IM_KEY_F;
    case Qt::Key_G:
        return IM_KEY_G;
    case Qt::Key_H:
        return IM_KEY_H;
    case Qt::Key_I:
        return IM_KEY_I;
    case Qt::Key_J:
        return IM_KEY_J;
    case Qt::Key_K:
        return IM_KEY_K;
    case Qt::Key_L:
        return IM_KEY_L;
    case Qt::Key_M:
        return IM_KEY_M;
    case Qt::Key_N:
        return IM_KEY_N;
    case Qt::Key_O:
        return IM_KEY_O;
    case Qt::Key_P:
        return IM_KEY_P;
    case Qt::Key_Q:
        return IM_KEY_Q;
    case Qt::Key_R:
        return IM_KEY_R;
    case Qt::Key_S:
        return IM_KEY_S;
    case Qt::Key_T:
        return IM_KEY_T;
    case Qt::Key_U:
        return IM_KEY_U;
    case Qt::Key_V:
        return IM_KEY_V;
    case Qt::Key_W:
        return IM_KEY_W;
    case Qt::Key_X:
        return IM_KEY_X;
    case Qt::Key_Y:
        return IM_KEY_Y;
    case Qt::Key_Z:
        return IM_KEY_Z;

    case Qt::Key_Up:
        return IM_KEY_UP;
    case Qt::Key_Down:
        return IM_KEY_DOWN;
    case Qt::Key_Left:
        return IM_KEY_LEFT;
    case Qt::Key_Right:
        return IM_KEY_RIGHT;

    case Qt::Key_Escape:
        return IM_KEY_ESCAPE;

    case Qt::Key_F1:
        return IM_KEY_F1;
    case Qt::Key_F2:
        return IM_KEY_F2;
    case Qt::Key_F3:
        return IM_KEY_F3;
    case Qt::Key_F4:
        return IM_KEY_F4;
    case Qt::Key_F5:
		return IM_KEY_F5;
    case Qt::Key_F6:
		return IM_KEY_F6;
    case Qt::Key_F7:
        return IM_KEY_F7;
    case Qt::Key_F8:
        return IM_KEY_F8;
    case Qt::Key_F9:
        return IM_KEY_F9;
    case Qt::Key_F10:
        return IM_KEY_F10;
    case Qt::Key_F11:
        return IM_KEY_F11;
    case Qt::Key_F12:
        return IM_KEY_F12;

	default:
        LogManager::pushEvent(new LogEvent(LogEventType::ConsoleLogEvent,std::string("Unable to handle entered key."),LogLevel::ERROR));
        return IM_KEY_0;
	}
}

MouseButtonId QTInputManager::QTMouseEventToMouseButtonId(QMouseEvent* _event)
{
    switch (_event->button())
	{
        case Qt::LeftButton:
            return IM_MOUSE_LEFT;
        case Qt::RightButton:
            return IM_MOUSE_RIGHT;
        case Qt::MiddleButton:
            return IM_MOUSE_MIDDLE;

        default:
            LogManager::pushEvent(new LogEvent(LogEventType::ConsoleLogEvent,"Unable to handle mouse button.",LogLevel::ERROR));
            return IM_MOUSE_LEFT;
	}
}
