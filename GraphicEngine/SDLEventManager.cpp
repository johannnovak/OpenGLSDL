#include "SDLEventManager.h"

std::vector<SDLEventHandler*> SDLEventManager::s_eventHandlers;

SDLEventManager::SDLEventManager()
{
}


SDLEventManager::~SDLEventManager()
{
}

void SDLEventManager::registerSDLEventHandler(SDLEventHandler* _eventHandler)
{
	if (_eventHandler != NULL)
		s_eventHandlers.push_back(_eventHandler);
}

void SDLEventManager::unregisterSDLEventHandler(SDLEventHandler* _handler)
{
	if (_handler == NULL)
		return;

	int size = s_eventHandlers.size();
	for (int i = 0; i < size; ++i)
	{
		if (s_eventHandlers[i] == _handler)
		{
			if (size == 1)
				s_eventHandlers.clear();
			else
			{
				s_eventHandlers[i] = s_eventHandlers[size - 1];
				s_eventHandlers.pop_back();
			}

			break;
		}
	}
}

void SDLEventManager::pollSDLEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		for (int i = 0; i < s_eventHandlers.size(); ++i)
		{
			for (int j = 0; j < s_eventHandlers[i]->getMasks().size(); ++j)
			{
				if (s_eventHandlers[i]->getMasks()[j] == evt.type)
				{
					s_eventHandlers[i]->handleEvent(evt);
					break;
				}
			}
		}
	}
}
