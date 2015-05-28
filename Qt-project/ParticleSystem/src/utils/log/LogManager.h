#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#define LOGMANAGER_ERROR_LIMIT 10

#include <iostream>
#include <string>
#include <QGLWidget>

class LogManager
{

    public:
        LogManager();
        virtual ~LogManager();

    public:
        static void showError(const char* _msg);
        static void setWindow(QGLWidget* _win);

        static void print(std::string _str);

    private:
        static QGLWidget* s_window;
        static unsigned int s_errorCount;
};

#endif
