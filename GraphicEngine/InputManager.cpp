#include "InputManager.h"

InputManager* InputManager::s_instance = nullptr;

MouseMotion::MouseMotion() : dx(0), dy(0), x(0), y(0)
{}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
	if (s_instance != nullptr)
		return s_instance;
	
	LogManager::showError("You need to initialize the InputManager before calling getInstance()");
	return s_instance;
}

std::string InputManager::IMTypeToStr(InputManagerType _type)
{
	switch (_type)
	{
	case IM_TYPE_SDL:
		return "SDLInputManager";

	default:
		return "Undefined";
	}
}