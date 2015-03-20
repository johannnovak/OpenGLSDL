#pragma once

#define LOGMANAGER_ERROR_LIMIT 10

#include <SDL.h>

class LogManager
{
public:
	LogManager();
	virtual ~LogManager();

public:
	static void showError(const char* _msg);
	static void setWindow(SDL_Window* win);

private:
	static SDL_Window* s_window;
	static unsigned int s_errorCount;
};

