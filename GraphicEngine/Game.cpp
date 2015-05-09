#include "Game.h"

using namespace std;

Game::Game() : m_scene(), m_graphics(), m_mainCamera(nullptr)
{
}


Game::~Game()
{
}

void Game::initialize() 
{ 
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(0);
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(0);
	}

	LogManager::setWindow(m_window);

	SDL_GLContext mainContext = SDL_GL_CreateContext(m_window);
	if (mainContext == nullptr)
	{
		cout << "SDL_CreateContext Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return exit(0);
	}

	glewInit();

	SDLInputManager::initialize();
	SDLEventManager::registerSDLEventHandler((SDLEventHandler*)((SDLInputManager*)SDLInputManager::getInstance()));
	SDLEventManager::registerSDLEventHandler(m_quitEventHandler);

	glClearColor(0.127f, 0.127f, 0.127f, 1.0f);

	glEnable(GL_DEPTH_TEST);
}

void Game::loadContent()
{ 
	m_shader.load("Shaders/shader");
	m_shader.registerUniform("P", ShaderUniformType_PROJECTION);
	m_shader.registerUniform("V", ShaderUniformType_VIEW);
	m_shader.registerUniform("W", ShaderUniformType_WORLD);

	m_shader.registerAttribute("pos", ShaderAttributeType_POSITION);
	m_shader.registerAttribute("color", ShaderAttributeType_COLOR);

	m_graphics.setShader(&m_shader);

	m_cube = new Cube();

	SceneNode* cubeNode = new SceneNode(m_scene.getRootNode());
	cubeNode->setObject3D(m_cube);

	SceneNode* cameraNode = new SceneNode(m_scene.getRootNode());
	cameraNode->setPosition(0, 0, 5);

	m_mainCamera = new Camera(*cameraNode);

	m_scene.getRootNode().addChild(cubeNode);
	m_scene.getRootNode().addChild(cameraNode);
}

void Game::update(float _dt) 
{ 
	InputManager* inputManager = SDLInputManager::getInstance();
	inputManager->resetMouseMotion();

	SDLEventManager::pollSDLEvents();

	if (m_quitEventHandler->m_quit || inputManager->isKeyDown(KeyId::IM_KEY_ESCAPE))
		this->m_quit = true;

	if (inputManager->isKeyDown(KeyId::IM_KEY_UP) || inputManager->isKeyDown(KeyId::IM_KEY_Z))
		m_mainCamera->getSceneNode().translate(0, 0, -0.01f*_dt);
	if (inputManager->isKeyDown(KeyId::IM_KEY_DOWN) || inputManager->isKeyDown(KeyId::IM_KEY_S))
		m_mainCamera->getSceneNode().translate(0, 0, 0.01f*_dt);
	if (inputManager->isKeyDown(KeyId::IM_KEY_RIGHT) || inputManager->isKeyDown(KeyId::IM_KEY_D))
		m_mainCamera->getSceneNode().translate(0.01f*_dt, 0, 0);
	if (inputManager->isKeyDown(KeyId::IM_KEY_LEFT) || inputManager->isKeyDown(KeyId::IM_KEY_Q))
		m_mainCamera->getSceneNode().translate(-0.01f*_dt, 0, 0);

	if (inputManager->isKeyDown(KeyId::IM_KEY_A))
		m_mainCamera->getSceneNode().translate(0, -0.01f*_dt, 0);
	if (inputManager->isKeyDown(KeyId::IM_KEY_E))
		m_mainCamera->getSceneNode().translate(0, 0.01f*_dt, 0);
}

void Game::draw(float _dt) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.activate();
	m_shader.transmitUniformMat4(ShaderUniformType_VIEW, &m_mainCamera->getView()[0][0], GL_FALSE);
	m_shader.transmitUniformMat4(ShaderUniformType_PROJECTION, &m_mainCamera->getProjection()[0][0], GL_FALSE);

	m_graphics.drawScene(m_scene);
	SDL_GL_SwapWindow(m_window);
}

void Game::unloadContent() 
{
	delete m_cube;
	delete m_mainCamera;
}