#include <Game.h> // Implemented class.

#include "LogManager.h"
#include "QTInputManager.h"
#include "OBJImporter.h"

#include "glm/glm.hpp"
#include <iostream>
#include <vector>

using namespace std;

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name: Game()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
Game::Game(): m_scene(), m_graphics(), m_mainCamera(nullptr), m_particleSystem()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Creating Game...");

    setWindowTitle(trUtf8("ParticleSystem"));
    //show();

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Game created.");
}


/**************************************************************************
* Name: ~Game()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
Game::~Game()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Destroying Game...");

    delete m_mainCamera;

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Game destroyed.");
}

/////////////////////////////// PROTECTED ///////////////////////////////////

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: initializeObjects()
* Description: Method used to initialize all of the objects of the scene
*						along with the shader attributes registering. All created
*						are added to the scene inside SceneNodes.
* Inputs: none
* Returns:
*			- True if no errors occurerd.
*			- False otherwise.
**************************************************************************/
bool Game::initializeObjects()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Initializing Objects...");

    m_particleSystem.initialize();
    m_atmosphericParticle.initialize();
    m_fireParticle.initialize();

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Loading Shaders...");

    m_shader.load("Shaders/light_shader");
    m_shader.registerUniform("P", ShaderUniformType_PROJECTION);
    m_shader.registerUniform("V", ShaderUniformType_VIEW);
    m_shader.registerUniform("W", ShaderUniformType_WORLD);

    m_shader.registerAttribute("pos", ShaderAttributeType_POSITION);
    m_shader.registerAttribute("color", ShaderAttributeType_COLOR);
    m_shader.registerAttribute("normal", ShaderAttributeType_NORMAL);

    m_graphics.setShader(&m_shader);

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Loaded and set.");

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Creating world entities...");

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
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "World entities created and added to the scene.");

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Object initialization successful.");
    return true;
}

/**************************************************************************
* Name: updateGame(float32 _dt)
* Description: Method used to update the different objects that composes
*						the scene. This is where the inputs can be tested
*						by the InputManager in order to move/delete objects,
*						stop the program, change parameters, etc ...
* Input:
*			- _dt : float32, time interval since the last rendering.
* Returns: none
**************************************************************************/
void Game::updateGame(float32 _dt)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Updating scene...");

    InputManager* inputManager = QTInputManager::getInstance();
    inputManager->resetMouseMotion();

    if (inputManager->isKeyDown(KeyId::IM_KEY_ESCAPE))
    {
        LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "ESCAPE key pressed.");

        LogManager::closeHandlers();

        close();
        parentWidget()->parentWidget()->parentWidget()->close();
    }

    glm::vec3 forward, right, up;
    glm::mat4 view = m_mainCamera->getSceneNode().computeWorldMatrix();

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
        float32 dx = inputManager->getMouseMotion().dx;
        float32 dy = inputManager->getMouseMotion().dy;

        m_mainCamera->getSceneNode().rotate(100.0f * dy, right);
        m_mainCamera->getSceneNode().rotate(-100.0f * dx , glm::vec3(0, 1, 0));
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

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Scene updated.");
}

/**************************************************************************
* Name: renderGame(float32 _dt)
* Description: Method used to do the rendering. It transmits shader variables
*					, tells the graphicsEngine to draw the scene, but also
*					draws other objects.
* Inputs:
*			- _dt : float32, time interval since the last rendering.
* Returns: none
**************************************************************************/
void Game::renderGame(float32 _dt)
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Rendering Scene...");

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

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Scene rendered.");
}


/**************************************************************************
* Name: getScene()
* Description: Getter for the 'm_scene' attribute.
* Inputs: none
* Returns: 'm_scene' attribute.
**************************************************************************/
Scene Game::getScene()
{
    return m_scene;
}
