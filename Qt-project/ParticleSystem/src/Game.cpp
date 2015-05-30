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
    installEventFilter(InputManager::getInstance());
    show();
    cout << "Game created !" << endl;
}


Game::~Game()
{

}

void Game::go()
{
    float dt = 0.0f;
    long targetTPF = (long) (1.0 / (double)m_targetFps * 1000.0); // time per frame

    while (!m_quit)
    {
        auto start = chrono::high_resolution_clock::now();

        m_globalTime += dt;
        updateGame(dt);
        paintGL(dt);

        auto dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
        if (dur.count() < targetTPF)
            this_thread::sleep_for(chrono::milliseconds(targetTPF - dur.count()));

        dt = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
    }

//	unloadContent();
}

bool Game::initializeObjects()
{
    cout << "Objects initialization " << endl;
    LogManager::setWindow(this);


    m_particleSystem.initialize();
    m_atmosphericParticle.initialize();
    m_fireParticle.initialize();

    cout << "Particle systems loaded !" << endl;

    m_shader.load("Shaders/light_shader");
    m_shader.registerUniform("P", ShaderUniformType_PROJECTION);
    m_shader.registerUniform("V", ShaderUniformType_VIEW);
    m_shader.registerUniform("W", ShaderUniformType_WORLD);

    m_shader.registerAttribute("pos", ShaderAttributeType_POSITION);
    m_shader.registerAttribute("color", ShaderAttributeType_COLOR);
    m_shader.registerAttribute("normal", ShaderAttributeType_NORMAL);

    m_graphics.setShader(&m_shader);

    cout << "Graphic's' current shader loaded !" << endl;

    m_cube = new Cube();

    m_cubeNode = new SceneNode(m_scene.getRootNode());
    m_cubeNode->setObject3D(m_cube);
    m_cubeNode->setPosition(0, 0.5f, 0);

    cout << "Cube created " << endl;

    SceneNode* cameraNode = new SceneNode(m_scene.getRootNode());
    cameraNode->setPosition(0, 1, 5);

    m_mainCamera = new Camera(*cameraNode);

    cout << "Camera created" << endl;
/*
    m_importedObject = OBJImporter::importObject("Ressources/Room.obj");

    cout << "Room imported" << endl;

    m_importedObject->setColor(1, 0, 0);
    m_importedObjectNode = new SceneNode(m_scene.getRootNode());
    m_importedObjectNode->setObject3D(m_importedObject);
    m_importedObjectNode->setPosition(0, 0, 0);

    cout << "Room imported" << endl;
*/
    m_scene.getRootNode()->addChild(m_cubeNode);
    m_scene.getRootNode()->addChild(cameraNode);
/*    m_scene.getRootNode()->addChild(m_importedObjectNode);
*/
    cout << "Cube/camera/room added in scene" << endl;
    return true;
}


void Game::render(float _dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_shader.activate();
        m_shader.transmitUniformMat4(ShaderUniformType_VIEW, &m_mainCamera->getView()[0][0], GL_FALSE);
        m_shader.transmitUniformMat4(ShaderUniformType_PROJECTION, &m_mainCamera->getProjection()[0][0], GL_FALSE);

        m_graphics.drawScene(m_scene);

        m_particleSystem.setProjection(&m_mainCamera->getProjection()[0][0]);
        m_particleSystem.setView(&m_mainCamera->getView()[0][0]);
        m_particleSystem.setWorld(&glm::mat4(1)[0][0]);
        m_particleSystem.draw(_dt);

    // 	m_atmosphericParticle.setProjection(&m_mainCamera->getProjection()[0][0]);
    // 	m_atmosphericParticle.setView(&m_mainCamera->getView()[0][0]);
    // 	m_atmosphericParticle.setWorld(&glm::mat4(1)[0][0]);
    // 	m_atmosphericParticle.draw(_dt);

        m_fireParticle.setMatrices(&glm::mat4(1)[0][0], &m_mainCamera->getView()[0][0], &m_mainCamera->getProjection()[0][0]);
        m_fireParticle.draw(_dt);
}

void Game::keyPressEvent( QKeyEvent* event )
{
    int key = event->key();
    switch(key)
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}
