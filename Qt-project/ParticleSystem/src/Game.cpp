#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game():GlWindow()
{
    setWindowTitle(trUtf8("ParticleSystem"));
    show();
}


Game::~Game()
{

}


bool Game::initializeObjects()
{

    LogManager::setWindow(this);

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    return true;
}


void Game::render()
{

}

void Game::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}
