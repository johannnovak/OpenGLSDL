#ifndef __QTINPUTMANAGER_H__
#define __QTINPUTMANAGER_H__

#include "LogManager.h"
#include "InputManager.h"

#include <vector>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>


/**************************************************************************
* Class: QTInputManager
* Description: Singleton class inheriting from InputManager (in order
*						to be generic) and QWidget (in order to catch keyboard
*						and mouse events).
*
**************************************************************************/
class QTInputManager : public InputManager, public QWidget
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* Array of boolean. Each value is associated with a key.
        *	1 means the key is pressed; 0 means the  key is released.
        */
        bool* m_keyPressed;

        /* Array of boolean, same as above, but concerns the mouse buttons. */
        bool* m_mouseButtonPressed;

        /* MouseMotion objet that allows to get informations on the position of
        *	mouse.
        */
        MouseMotion m_mouseMotion;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  QTInputManager()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        QTInputManager();

        /**************************************************************************
        * Name:  ~QTInputManager()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~QTInputManager();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name:  getMouseMotion()
        * Description: Abstract getter for the 'm_mouseMotion' attribute the inherited class
        *						has to possess.
        * Inputs: none
        * Returns:
        *			- m_mouseMotion : MouseMotion&, reference on the MouseMotion attribute.
        **************************************************************************/
        virtual MouseMotion& getMouseMotion();

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name:  initialize()
        * Description: Method designed to create the new instance of the class :
        *					's_instance'.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        static void initialize();

        /**************************************************************************
        * Name:  resetMouseMotion()
        * Description: Method used to reset the mouse motion attributes to 0.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        void resetMouseMotion();

/////////////////////////////// PUBLIC ///////////////////////////////////
    protected:

        /**************************************************************************
        * Name:  eventFilter(QObject* _object,QEvent* _event)
        * Description: Method used to filter events. In our case, the method filters
        *				QEvent::KeyPress, QEvent::KeyRelease, QEvent::MouseMove,
        *				QEvent::MouseButtonPress, QEvent::MouseButtonRelease.
        * Inputs:
        *			- _object : QObject*, QObject that received an event.
        *			- _event  : QEvent*, event that the QObject received.
        * Returns:
        *			- True if the event has been filtered.
        *			- False otherwise.
        **************************************************************************/
        bool eventFilter(QObject* _object,QEvent* _event);

        /**************************************************************************
        * Name:  keyPressEvent(QKeyEvent* _event)
        * Description: Method used when a QEvent::KeyPressed has been filtered.
        *				It transforms the Qt::Key into an KeyId and sets
        *				the InputManager 'm_keyPressed' associated index to true.
        * Inputs:
        *			- _event  : QKeyEvent*, event which has been filtered.
        * Returns: none
        **************************************************************************/
        void keyPressEvent(QKeyEvent* _event);

        /**************************************************************************
        * Name:  keyReleaseEvent(QKeyEvent* _event)
        * Description: Method used when a QEvent::KeyReleased has been filtered.
        *				It transforms the Qt::Key into an KeyId and sets
        *				the InputManager 'm_keyPressed' associated index to false.
        * Inputs:
        *			- _event  : QKeyEvent*, event which has been filtered.
        * Returns: none
        **************************************************************************/
        void keyReleaseEvent(QKeyEvent* _event);

        /**************************************************************************
        * Name:  mouseMoveEvent(QMouseEvent* _event)
        * Description: Method used when a QEvent::MouseMoved has been filtered.
        *				It sets the different atrtibutes of the MouseMotion.
        * Inputs:
        *			- _event  : QMouseEvent*, event which has been filtered.
        * Returns: none
        **************************************************************************/
        void mouseMoveEvent(QMouseEvent* _event);

        /**************************************************************************
        * Name:  mousePressEvent(QMouseEvent* _event)
        * Description: Method used when a QEvent::MouseButtonPressed has been filtered.
        *				It transforms the QMouseButton into an MouseButtonId and sets
        *				the InputManager 'm_mouseButtonPressed' associated index to true.
        * Inputs:
        *			- _event  : QMouseEvent*, event which has been filtered.
        * Returns: none
        **************************************************************************/
        void mousePressEvent(QMouseEvent* _event);

        /**************************************************************************
        * Name:  mouseReleaseEvent(QMouseEvent* _event)
        * Description: Method used when a QEvent::MouseButtonReleased has been filtered.
        *				It transforms the QMouseButton into an MouseButtonId and sets
        *				the InputManager 'm_mouseButtonPressed' associated index to false.
        * Inputs:
        *			- _event  : QMouseEvent*, event which has been filtered.
        * Returns: none
        **************************************************************************/
        void mouseReleaseEvent(QMouseEvent* _event);

/////////////////////////////// PRIVATE ///////////////////////////////////
    private:

        /**************************************************************************
        * Name: QTKeyEventToKeyId(QKeyEvent* _event)
        * Description: Method used to transform a QKeyEvent* into a KeyId.
        * Inputs:
        *			- _event  : QKeyEvent*, event to transform into a KeyId.
        * Returns:
        *			- KeyId associated to the QKeyEvent.
        **************************************************************************/
        static KeyId QTKeyEventToKeyId(QKeyEvent* _event);

        /**************************************************************************
        * Name: QTMouseEventToMouseButtonId(QMouseEvent* _event)
        * Description: Method used to transform a QMouseEvent* into a MouseButtonId.
        * Inputs:
        *			- _event  : QMouseEvent*, event to transform into a MouseButtonId.
        * Returns:
        *			- MouseButtonId associated with the QMouseEvent.
        **************************************************************************/
        static MouseButtonId QTMouseEventToMouseButtonId(QMouseEvent* _event);

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= INQUIRY ==============================================

        /**************************************************************************
        * Name:  isKeyDown(KeyId _keyId)
        * Description: Method used to tell if a certain key is being pressed.
        * Inputs:
        *			- _keyId : KeyID, id of the key to check if it is pressed or not.
        * Returns:
        *			- True if the key associated with the KeyId is pressed.
        *			- False otherwise.
        **************************************************************************/
        bool isKeyDown(KeyId _keyId);

        /**************************************************************************
        * Name:  isKeyUp(KeyId _keyId)
        * Description: Method used to tell if a certain key is released.
        * Inputs:
        *			- _keyId : KeyID, id of the key to check if it is released or not.
        * Returns:
        *			- True if the key associated with the KeyId is released.
        *			- False otherwise.
        **************************************************************************/
        bool isKeyUp(KeyId _keyId);


        /**************************************************************************
        * Name:  isMouseButtonDown(MouseButtonId _mouseId)
        * Description: Method used to tell if a certain mouse button is pressed.
        * Inputs:
        *			- _mouseId : MouseButtonID, id of the mouse button to check if it is
        *								pressed or not.
        * Returns:
        *			- True if the mouse button associated with the MouseButtonId is pressed.
        *			- False otherwise.
        **************************************************************************/
        bool isMouseButtonDown(MouseButtonId _mouseId);

        /**************************************************************************
        * Name:  isMouseButtonUp(MouseButtonId _mouseId)
        * Description: Method used to tell if a certain mouse button is released.
        * Inputs:
        *			- _mouseId : MouseButtonID, id of the mouse button to check if it is
        *								released or not.
        * Returns:
        *			- True if the mouse button associated with the MouseButtonId is released.
        *			- False otherwise.
        **************************************************************************/
        bool isMouseButtonUp(MouseButtonId _mouseId);
};

#endif // __QTINPUTMANAGER_H__
