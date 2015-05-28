#include <Game.h>
#include <iostream>
#include <vector>

#include "LogManager.h"
#include "OBJImporter.h"

using namespace std;

Game::Game(): m_scene(), m_graphics(), m_mainCamera(nullptr), m_particleSystem()
{
    cout << "Game creation" << endl;
    setWindowTitle(trUtf8("ParticleSystem"));
    show();
    cout << "Game created !" << endl;
}


Game::~Game()
{

}


bool Game::initializeObjects()
{
    cout << "Objects initialization " << endl;
    LogManager::setWindow(this);


    m_particleSystem.initialize();
    cout << "dgdfgfdgfdg" << endl;
    m_atmosphericParticle.initialize();
    m_fireParticle.initialize();

    cout << "dgdfgfdgfdg" << endl;

    m_shader.load("Shaders/light_shader");
    m_shader.registerUniform("P", ShaderUniformType_PROJECTION);
    m_shader.registerUniform("V", ShaderUniformType_VIEW);
    m_shader.registerUniform("W", ShaderUniformType_WORLD);

    m_shader.registerAttribute("pos", ShaderAttributeType_POSITION);
    m_shader.registerAttribute("color", ShaderAttributeType_COLOR);
    m_shader.registerAttribute("normal", ShaderAttributeType_NORMAL);

    cout << "dgdfgfdgfdg" << endl;
    m_graphics.setShader(&m_shader);

    m_cube = new Cube();

    m_cubeNode = new SceneNode(m_scene.getRootNode());
    m_cubeNode->setObject3D(m_cube);
    m_cubeNode->setPosition(0, 0.5f, 0);

    SceneNode* cameraNode = new SceneNode(m_scene.getRootNode());
    cameraNode->setPosition(0, 1, 5);

    m_mainCamera = new Camera(*cameraNode);

    cout << "dgdfgfdgfdg" << endl;
    m_importedObject = OBJImporter::importObject("Ressources/Room.obj");
    m_importedObject->setColor(1, 0, 0);
    m_importedObjectNode = new SceneNode(m_scene.getRootNode());
    m_importedObjectNode->setObject3D(m_importedObject);
    m_importedObjectNode->setPosition(0, 0, 0);

    m_scene.getRootNode()->addChild(m_cubeNode);
    m_scene.getRootNode()->addChild(cameraNode);
    m_scene.getRootNode()->addChild(m_importedObjectNode);

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
