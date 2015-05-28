#pragma once

#include <vector>
#include <SDL.h>

class SDLEventHandler
{
public:
	SDLEventHandler();
	~SDLEventHandler();

	virtual void handleEvent(SDL_Event& _event) = 0;
	virtual std::vector<SDL_EventType>& getMasks() = 0;
};

