#include "Game.h"
#include "QTInputManager.h"
#include "ConsoleLogEventHandler.h"
#include "QTLogEventHandler.h"
#include "MainWindow.h"
#include <QApplication>

int main(int _argc, char* _argv[])
{
    QApplication app(_argc, _argv);

    QTInputManager::initialize();

    LogManager::registerLogEventHandler(new ConsoleLogEventHandler());
    LogManager::registerLogEventHandler(new QTLogEventHandler());

    Game* game = new Game();

    app.installEventFilter((QTInputManager*)InputManager::getInstance());

    MainWindow win;
    win.addOpenGlWidget(game);
    win.show();

    int result = app.exec();

    delete game;
    LogManager::unregisterAllLogEventHandler();

    return result;
}
