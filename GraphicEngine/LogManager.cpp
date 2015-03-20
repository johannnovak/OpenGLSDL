#include "LogManager.h"

SDL_Window* LogManager::s_window = NULL;
unsigned int LogManager::s_errorCount = 0;

LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

void LogManager::setWindow(SDL_Window* _win)
{
	s_window = _win;
}

void LogManager::showError(const char* _msg)
{
	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error", _msg, LogManager::s_window);
	s_errorCount++;

	if (s_errorCount > LOGMANAGER_ERROR_LIMIT)
		exit(1);
}

void LogManager::print(std::string _str)
{
	std::cout << _str << std::endl;
}