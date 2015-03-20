#pragma once

#define LOGMANAGER_ERROR_LIMIT 10

#include <iostream>
#include <string>

#include <SDL.h>

class LogManager
{
public:
	LogManager();
	virtual ~LogManager();

public:
	static void showError(const char* _msg);
	static void setWindow(SDL_Window* _win);

	static void print(std::string _str);

private:
	static SDL_Window* s_window;
	static unsigned int s_errorCount;
};

