#include "LogManager.h"
#include <QDebug>
#include <string>

QGLWidget* LogManager::s_window = NULL;
unsigned int LogManager::s_errorCount = 0;

LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

void LogManager::setWindow(QGLWidget* _win)
{
	s_window = _win;
}

void LogManager::showError(const char* _msg)
{
//	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error", _msg, LogManager::s_window);
    std::string error("Error : ");
    error += _msg;

    std::cout << error << std::endl;

    s_errorCount++;

	if (s_errorCount > LOGMANAGER_ERROR_LIMIT)
    {
        std::cout << "Too many errors, program exiting\n\n" << endl;
        exit(1);
    }
}

void LogManager::print(std::string _str)
{
	std::cout << _str << std::endl;
}
