#include "GlWindow.h"


GlWindow::GlWindow():m_targetFps(60), m_globalTime(0), m_quit(false)
{
    resize(1024, 768);
}

GlWindow::~GlWindow()
{
}

void GlWindow::initializeGL()
{
    init();
    initializeObjects();
}


void GlWindow::updateGame(float _dt)
{
    InputManager* inputManager = SDLInputManager::getInstance();
    inputManager->resetMouseMotion();

    SDLEventManager::pollSDLEvents();

    if (m_quitEventHandler->m_quit || inputManager->isKeyDown(KeyId::IM_KEY_ESCAPE))
        this->m_quit = true;

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
}


void GlWindow::paintGL(float _dt)
{
    /* Draws the scene and its child. */
    render(_dt);

    /* Updates QT window. */
    update();
}


void GlWindow::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );

    float a = w / static_cast<GLfloat>(h);
//	printf( "Size: (%d,%d) - AspectRatio: %f\n", w, h, a );

    setPerspective( 45.0f, a, 0.1f, 100.0f );
}
