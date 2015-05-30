#ifndef QTINPUTMANAGER_H
#define QTINPUTMANAGER_H

#include <vector>
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>

#include "LogManager.h"
#include "InputManager.h"


class QTInputManager :
    public InputManager, public QObject
{
    public:
        QTInputManager();
        virtual ~QTInputManager();

        static void initialize();

        bool isKeyDown(KeyId _keyId);
        bool isKeyUp(KeyId _keyId);

        bool isMouseButtonDown(MouseButtonId _mouseId);
        bool isMouseButtonUp(MouseButtonId _mouseId);

        MouseMotion& getMouseMotion();
        void resetMouseMotion();

        void handleEvent(SDL_Event& _event);
        std::vector<SDL_EventType>& getMasks();

        static KeyId QTKeyEventToKeyId(QKeyEvent* _event);
        static MouseButtonId QTMouseEventToMouseButtonId(QMouseEvent* _event);

    protected:
        bool event( QEvent *evt );

    private:
        bool* m_keyPressed;
        bool* m_mouseButtonPressed;

        MouseMotion m_mouseMotion;

        std::vector<QEvent> m_eventMasks;
};

#endif
