#include "Game.h"
#include "QTInputManager.h"

#include <QApplication>
#include "QTInputManager.h"
#include "ConsoleLogEventHandler.h"
#include "QTLogEventHandler.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTInputManager::initialize();
    LogManager::registerLogEventHandler(new ConsoleLogEventHandler());
    LogManager::registerLogEventHandler(new QTLogEventHandler());

    Game game;

    app.installEventFilter((QTInputManager*)InputManager::getInstance());

    return app.exec();
}
