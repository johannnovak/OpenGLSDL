#include "Game.h"
#include "QTInputManager.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Game game;
    app.installEventFilter((QTInputManager*)InputManager::getInstance());
    return app.exec();
}
