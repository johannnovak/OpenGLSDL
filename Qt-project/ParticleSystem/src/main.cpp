#include "Game.h"
#include "QTInputManager.h"

#include <QApplication>
#include "QTInputManager.h"
#include "ConsoleLogEventHandler.h"
#include "QTLogEventHandler.h"

int main(int _argc, char* _argv[])
{
    QApplication app(_argc, _argv);

    QTInputManager::initialize();
    LogManager::registerLogEventHandler(new ConsoleLogEventHandler());
    LogManager::registerLogEventHandler(new QTLogEventHandler());

    Game game;

    app.installEventFilter((QTInputManager*)InputManager::getInstance());

    return app.exec();
}
