#include "Game.h"
#include "InputManager.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Game game;
    app.exec();
    game.go();
}
