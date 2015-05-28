#pragma once

#include <vector>
#include <SDL.h>

#include "SDLEventHandler.h"

class SDLEventManager
{
public:
	SDLEventManager();
	~SDLEventManager();

public:
	static void registerSDLEventHandler(SDLEventHandler* _handler);
	static void unregisterSDLEventHandler(SDLEventHandler* _handler);
	static void pollSDLEvents();

private:
	static std::vector<SDLEventHandler*> s_eventHandlers;
};

