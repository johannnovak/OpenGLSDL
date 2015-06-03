#include "InputManager.h"

InputManager* InputManager::s_instance = nullptr;

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  MouseMotion()
* Description: Default constructor. Default values are set to 0.
* Inputs: none
**************************************************************************/
MouseMotion::MouseMotion() : dx(0), dy(0), x(0), y(0)
{}

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  InputManager()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
InputManager::InputManager()
{
}

/**************************************************************************
* Name:  ~InputManager()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
InputManager::~InputManager()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name:  getInstance()
* Description: Getter for the 's_instance' attribute.
* Inputs: none
* Returns:
*			- s_instance : InputManager*, instance of the class' singleton.
**************************************************************************/
InputManager* InputManager::getInstance()
{
	if (s_instance != nullptr)
		return s_instance;
	
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_ERROR, "You need to initialize the InputManager before calling getInstance()");
    return s_instance;
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name:  std::string IMTypeToStr(InputManagerType _type)
* Description: Method used to transform any InputManagerType into a string.
* Inputs:
*			- _type : InputManagerType, enum to return as a string.
* Returns:
*			- String value of the enum.
**************************************************************************/
std::string InputManager::IMTypeToStr(InputManagerType _type)
{
	switch (_type)
	{
        case IM_TYPE_SDL:
            return "SDLInputManager";

        case IM_TYPE_QT:
            return "QTInputManager";

        default:
            return "Undefined";
	}
}
