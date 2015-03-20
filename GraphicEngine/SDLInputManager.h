#pragma once

#include <vector>

#include "InputManager.h"
#include "SDLEventHandler.h"

#include "LogManager.h"

class SDLInputManager :
	public InputManager, public SDLEventHandler
{
public:
	SDLInputManager();
	virtual ~SDLInputManager();

	static void initialize();

	bool isKeyDown(KeyId _keyId);
	bool isKeyUp(KeyId _keyId);

	bool isMouseButtonDown(MouseButtonId _mouseId);
	bool isMouseButtonUp(MouseButtonId _mouseId);

	MouseMotion& getMouseMotion();

	void handleEvent(SDL_Event& _event);
	std::vector<SDL_EventType>& getMasks();

	static KeyId SDLKeyToKeyId(SDL_Keycode _sdlk);
	static MouseButtonId SDLMouseButtonToMouseButtonId(Uint8 _sdlMouseButton);

private:
	bool* m_keyPressed;
	bool* m_mouseButtonPressed;

	MouseMotion m_mouseMotion;

	std::vector<SDL_EventType> m_eventMasks;
};

