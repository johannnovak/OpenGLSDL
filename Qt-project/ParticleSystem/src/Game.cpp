#include <Game.h>
#include <iostream>
#include <vector>

#include "LogManager.h"
#include "glm/glm.hpp"
#include "QTInputManager.h"
#include "OBJImporter.h"

using namespace std;

Game::Game(): m_scene(), m_graphics(), m_mainCamera(nullptr), m_particleSystem()
{
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::INFO, "Creating Game..."));

    setWindowTitle(trUtf8("ParticleSystem"));
    show();

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Game created."));
}


Game::~Game()
{
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::INFO, "Destroying Game..."));

    delete m_mainCamera;

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Game destroyed."));
}

bool Game::initializeObjects()
{
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::INFO, "Initializing Objects..."));

    m_particleSystem.initialize();
    m_atmosphericParticle.initialize();
    m_fireParticle.initialize();

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Loading Shaders..."));

    m_shader.load("Shaders/light_shader");
    m_shader.registerUniform("P", ShaderUniformType_PROJECTION);
    m_shader.registerUniform("V", ShaderUniformType_VIEW);
    m_shader.registerUniform("W", ShaderUniformType_WORLD);

    m_shader.registerAttribute("pos", ShaderAttributeType_POSITION);
    m_shader.registerAttribute("color", ShaderAttributeType_COLOR);
    m_shader.registerAttribute("normal", ShaderAttributeType_NORMAL);

    m_graphics.setShader(&m_shader);

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Loaded and set."));

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Creating world entities..."));

    m_cube = new Cube();

    m_cubeNode = new SceneNode(m_scene.getRootNode());
    m_cubeNode->setObject3D(m_cube);
    m_cubeNode->setPosition(0, 0.5f, 0);

    SceneNode* cameraNode = new SceneNode(m_scene.getRootNode());
    cameraNode->setPosition(0, 1, 5);

    m_mainCamera = new Camera(*cameraNode);

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
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "World entities created and added to the scene."));

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::INFO, "Object initialization successful."));
    return true;
}

void Game::updateGame(float _dt)
{
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Updating scene..."));

    InputManager* inputManager = QTInputManager::getInstance();
    inputManager->resetMouseMotion();

    if (LogManager::s_errorCount > 10 || inputManager->isKeyDown(KeyId::IM_KEY_ESCAPE))
    {
        if (LogManager::s_errorCount > 10)
            LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::ERROR, "Too many errors, exiting the program."));
        else
            LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::INFO, "ESCAPE key pressed."));

        LogManager::closeHandlers();

        close();
    }

    glm::vec3 forward, right, up;
    glm::mat4 view = m_mainCamera->getSceneNode().computeWorldMatrice();

    right.x = view[0].x;
    right.y = view[1].x;
    right.z = view[2].x;

    up.x = view[0].y;
    up.y = view[1].y;
    up.z = view[2].y;

    forward.x = view[0].z;
    forward.y = view[1].z;
    forward.z = view[2].z;

    if (inputManager->isKeyDown(KeyId::IM_KEY_UP) || inputManager->isKeyDown(KeyId::IM_KEY_Z))
        m_mainCamera->getSceneNode().translate(-0.01f*_dt * forward);
    if (inputManager->isKeyDown(KeyId::IM_KEY_DOWN) || inputManager->isKeyDown(KeyId::IM_KEY_S))
        m_mainCamera->getSceneNode().translate(0.01f*_dt * forward);
    if (inputManager->isKeyDown(KeyId::IM_KEY_RIGHT) || inputManager->isKeyDown(KeyId::IM_KEY_D))
        m_mainCamera->getSceneNode().translate(0.01f*_dt * right);
    if (inputManager->isKeyDown(KeyId::IM_KEY_LEFT) || inputManager->isKeyDown(KeyId::IM_KEY_Q))
        m_mainCamera->getSceneNode().translate(-0.01f*_dt * right);

    if (inputManager->isKeyDown(KeyId::IM_KEY_A))
        m_mainCamera->getSceneNode().translate(0, -0.01f*_dt, 0);
    if (inputManager->isKeyDown(KeyId::IM_KEY_E))
        m_mainCamera->getSceneNode().translate(0, 0.01f*_dt, 0);

    // rotate camera
    if (inputManager->isMouseButtonDown(IM_MOUSE_RIGHT))
    {
        float dx = inputManager->getMouseMotion().dx;
        float dy = inputManager->getMouseMotion().dy;

        m_mainCamera->getSceneNode().rotate(0.005f * dy, right);
        m_mainCamera->getSceneNode().rotate(-0.005f * dx , glm::vec3(0, 1, 0));
    }

    if (inputManager->isKeyDown(KeyId::IM_KEY_L))
        m_cubeNode->rotate(0.01f, glm::vec3(0, 1, 0));
    if (inputManager->isKeyDown(KeyId::IM_KEY_J))
        m_cubeNode->rotate(-0.01f, glm::vec3(0, 1, 0));
    if (inputManager->isKeyDown(KeyId::IM_KEY_I))
        m_cubeNode->translate(0, 0, 0.01f*_dt);
    if (inputManager->isKeyDown(KeyId::IM_KEY_K))
        m_cubeNode->translate(0, 0, -0.01f*_dt);

    if (inputManager->isKeyDown(KeyId::IM_KEY_P))
        m_mainCamera->getSceneNode().rotate(0.01f, glm::vec3(0, 1, 0));
    if (inputManager->isKeyDown(KeyId::IM_KEY_O))
        m_mainCamera->getSceneNode().rotate(-0.01f, glm::vec3(0, 1, 0));

    if (inputManager->isKeyDown(KeyId::IM_KEY_R))
    {
        m_mainCamera->getSceneNode().setPosition(0, 0, 5);
        m_mainCamera->getSceneNode().setRotation(0, 0, 0);
    }

    m_particleSystem.update(_dt);
    m_fireParticle.update(_dt);
    m_atmosphericParticle.update(_dt);

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Scene updated."));
}

void Game::renderGame(float _dt)
{
    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Rendering Scene..."));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.activate();
    m_shader.transmitUniformMat4(ShaderUniformType_VIEW, &m_mainCamera->getView()[0][0], GL_FALSE);
    m_shader.transmitUniformMat4(ShaderUniformType_PROJECTION, &m_mainCamera->getProjection()[0][0], GL_FALSE);

    m_graphics.drawScene(m_scene);

    m_particleSystem.setProjection(&m_mainCamera->getProjection()[0][0]);
    m_particleSystem.setView(&m_mainCamera->getView()[0][0]);
    m_particleSystem.setWorld(&glm::mat4(1)[0][0]);
    m_particleSystem.draw(_dt);

    m_atmosphericParticle.setProjection(&m_mainCamera->getProjection()[0][0]);
    m_atmosphericParticle.setView(&m_mainCamera->getView()[0][0]);
    m_atmosphericParticle.setWorld(&glm::mat4(1)[0][0]);
    m_atmosphericParticle.draw(_dt);

    m_fireParticle.setMatrices(&glm::mat4(1)[0][0], &m_mainCamera->getView()[0][0], &m_mainCamera->getProjection()[0][0]);
    m_fireParticle.draw(_dt);

    LogManager::pushEvent(new LogEvent(LogEventType::ALL_LOG_EVENT, LogLevel::DEBUG, "Scene rendered."));
}
