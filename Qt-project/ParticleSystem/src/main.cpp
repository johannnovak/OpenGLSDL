﻿#include "Game.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Game game;
    return app.exec();
}
