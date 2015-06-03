#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>

#include "LogManager.h"

/**************************************************************************
* Enum: KeyId
* Description: Enum that specifies the for each possible key input, an
*						hexadecimal ID.
**************************************************************************/
enum KeyId
{
	IM_KEY_A = 0x00,
	IM_KEY_B = 0x01,
	IM_KEY_C = 0x02,
	IM_KEY_D = 0x03,
	IM_KEY_E = 0x04,
	IM_KEY_F = 0x05,
	IM_KEY_G = 0x06,
	IM_KEY_H = 0x07,
	IM_KEY_I = 0x08,
	IM_KEY_J = 0x09,
	IM_KEY_K = 0x0A,
	IM_KEY_L = 0x0B,
	IM_KEY_M = 0x0C,
	IM_KEY_N = 0x0D,
	IM_KEY_O = 0x0E,
	IM_KEY_P = 0x0F,
	IM_KEY_Q = 0x10,
	IM_KEY_R = 0x11,
	IM_KEY_S = 0x12,
	IM_KEY_T = 0x13,
	IM_KEY_U = 0x14,
	IM_KEY_V = 0x15,
	IM_KEY_W = 0x16,
	IM_KEY_X = 0x17,
	IM_KEY_Y = 0x18,
	IM_KEY_Z = 0x19,

	IM_KEY_1 = 0x1A,
	IM_KEY_2 = 0x1B,
	IM_KEY_3 = 0x1C,
	IM_KEY_4 = 0x1D,
	IM_KEY_5 = 0x1E,
	IM_KEY_6 = 0x1F,
	IM_KEY_7 = 0x20,
	IM_KEY_8 = 0x21,
	IM_KEY_9 = 0x22,
	IM_KEY_0 = 0x23,

	IM_KEY_UP = 0x24,
	IM_KEY_DOWN = 0x25,
	IM_KEY_LEFT = 0x26,
	IM_KEY_RIGHT = 0x27,

	IM_KEY_ESCAPE = 0x28,

	IM_KEY_F1 = 0x29,
    IM_KEY_F2 = 0x2A,
	IM_KEY_F3 = 0x2B,
	IM_KEY_F4 = 0x2C,
	IM_KEY_F5 = 0x2D,
	IM_KEY_F6 = 0x2E,
	IM_KEY_F7 = 0x2F,
	IM_KEY_F8 = 0x30,
	IM_KEY_F9 = 0x31,
	IM_KEY_F10 = 0x32,
	IM_KEY_F11 = 0x33,
	IM_KEY_F12 = 0x34,

	IM_KEY_LAST

};

/**************************************************************************
* Enum: MouseButtonId
* Description: Enum that specifies the for each possible mouse input, an
*						hexadecimal ID.
**************************************************************************/
enum MouseButtonId
{
	IM_MOUSE_LEFT = 0x0,
	IM_MOUSE_RIGHT = 0x1,
	IM_MOUSE_MIDDLE = 0x2,

	IM_MOUSE_LAST
};

/**************************************************************************
* Enum: InputManagerType
* Description: Enum that lists all class that inherits InputManager (application
*						specific, one for SDL, one for QT, etc ...).
**************************************************************************/
enum InputManagerType
{
    IM_TYPE_SDL = 0,
    IM_TYPE_QT = 1,

    IM_TYPE_LAST
};

/**************************************************************************
* Class: MouseMotion
* Description: Class that represents the different characteristics of the
*						motion of a mouse that are, its position on the screen
*						and its associated speed vector.
*
**************************************************************************/
class MouseMotion
{
/////////////////////////////// PUBLIC ///////////////////////////////////
    public:

        /* x position of the mouse. */
        int x;
        /* y position of the mouse. */
        int y;

        /* x component of the speed vector of the mouse. */
        int dx;
        /* y component of the speed vector of the mouse. */
        int dy;

  //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  MouseMotion()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        MouseMotion();
};

/**************************************************************************
* Class: InputManager
* Description: Singleton class designed to implement an abstract and general InputManager.
*						It has its own KeyIdentifiers for the keyboard and mouse and
*						handles its motion.
*
**************************************************************************/
class InputManager
{
/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:
        /* Singleton instance of the class. */
        static InputManager* s_instance;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  InputManager()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        InputManager();

        /**************************************************************************
        * Name:  ~InputManager()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~InputManager();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name:  getInstance()
        * Description: Getter for the 's_instance' attribute.
        * Inputs: none
        * Returns:
        *			- s_instance : InputManager*, instance of the class' singleton.
        **************************************************************************/
        static InputManager* getInstance();

        /**************************************************************************
        * Name:  getMouseMotion()
        * Description: Abstract getter for the 'm_mouseMotion' attribute the inherited class
        *						has to possess.
        * Inputs: none
        * Returns:
        *			- m_mouseMotion : MouseMotion&, reference on the MouseMotion attribute.
        **************************************************************************/
        virtual MouseMotion& getMouseMotion() = 0;

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name:  resetMouseMotion()
        * Description: Abstract method used to reset the mouse motion attributes to 0.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        virtual void resetMouseMotion() = 0;

        /**************************************************************************
        * Name:  std::string IMTypeToStr(InputManagerType _type)
        * Description: Method used to transform any InputManagerType into a string.
        * Inputs:
        *			- _type : InputManagerType, enum to return as a string.
        * Returns:
        *			- String value of the enum.
        **************************************************************************/
        static std::string IMTypeToStr(InputManagerType _type);

    //============================= INQUIRY ==============================================

        /**************************************************************************
        * Name:  isKeyDown(KeyId _keyId)
        * Description: Abstract method used to tell if a certain key is being pressed.
        * Inputs:
        *			- _keyId : KeyID, id of the key to check if it is pressed or not.
        * Returns:
        *			- True if the key associated with the KeyId is pressed.
        *			- False otherwise.
        **************************************************************************/
        virtual bool isKeyDown(KeyId _keyId) = 0;

        /**************************************************************************
        * Name:  isKeyUp(KeyId _keyId)
        * Description: Abstract method used to tell if a certain key is released.
        * Inputs:
        *			- _keyId : KeyID, id of the key to check if it is released or not.
        * Returns:
        *			- True if the key associated with the KeyId is released.
        *			- False otherwise.
        **************************************************************************/
        virtual bool isKeyUp(KeyId _keyId) = 0;


        /**************************************************************************
        * Name:  isMouseButtonDown(MouseButtonId _mouseId)
        * Description: Abstract method used to tell if a certain mouse button is pressed.
        * Inputs:
        *			- _mouseId : MouseButtonID, id of the mouse button to check if it is
        *								pressed or not.
        * Returns:
        *			- True if the mouse button associated with the MouseButtonId is pressed.
        *			- False otherwise.
        **************************************************************************/
        virtual bool isMouseButtonDown(MouseButtonId _mouseId) = 0;

        /**************************************************************************
        * Name:  isMouseButtonUp(MouseButtonId _mouseId)
        * Description: Abstract method used to tell if a certain mouse button is released.
        * Inputs:
        *			- _mouseId : MouseButtonID, id of the mouse button to check if it is
        *								released or not.
        * Returns:
        *			- True if the mouse button associated with the MouseButtonId is released.
        *			- False otherwise.
        **************************************************************************/
        virtual bool isMouseButtonUp(MouseButtonId _mouseId) = 0;

};

#endif // INPUTMANAGER_H
