#ifndef QTINPUTMANAGER_H
#define QTINPUTMANAGER_H

#include <vector>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

#include "LogManager.h"
#include "InputManager.h"

class QTInputManager :
    public InputManager, public QWidget
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

        std::vector<QEvent>& getMasks();

        static KeyId QTKeyEventToKeyId(QKeyEvent* _event);
        static MouseButtonId QTMouseEventToMouseButtonId(QMouseEvent* _event);

        bool eventFilter(QObject* _object,QEvent* _event);

    protected:
        void mousePressEvent(QMouseEvent* _event);
        void mouseReleaseEvent(QMouseEvent* _event);
        void mouseMoveEvent(QMouseEvent* _event);
        void keyPressEvent(QKeyEvent* _event);
        void keyReleaseEvent(QKeyEvent* _event);

    private:
        bool* m_keyPressed;
        bool* m_mouseButtonPressed;

        MouseMotion m_mouseMotion;

        std::vector<QEvent> m_eventMasks;
};
/*
#define INTERFACE_QTINPUTMANAGER\
    void mousePressEvent(QMouseEvent* _event);\
    void mouseMoveEvent(QMouseEvent* _event);\
    void keyPressEvent(QKeyEvent* _event);\
*/
#endif
