#pragma once

#include "GameEngine.h"

#include "Scene.h"
#include "Shader.h"
#include "InputManager.h"
#include "GraphicEngine.h"
#include "Camera.h"
#include "Cube.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "SDLEventManager.h"
#include "SDLInputManager.h"

class QuitEventHandler : public SDLEventHandler
{
public:
	QuitEventHandler() { m_quit = false; mask.push_back(SDL_QUIT); }
	~QuitEventHandler() { }

	void externQuit() { m_quit = true; }

	void handleEvent(SDL_Event& _event) {
		m_quit = true;
	}

	std::vector<SDL_EventType>& getMasks()
	{
		return mask;
	}

public:
	std::vector<SDL_EventType> mask;
	bool m_quit;
};

class Game : public GameEngine
{

public:
	Game();
	virtual ~Game();

protected:
	virtual void initialize();
	virtual void loadContent();

	virtual void update(float _dt);
	virtual void draw(float _dt);

	virtual void unloadContent();

private:
	Scene m_scene;
	Shader m_shader;
	GraphicEngine m_graphics;
	
	Camera* m_mainCamera;

	SceneNode* m_cubeNode;
	Cube* m_cube;

	Plane* m_plane;

	QuitEventHandler* m_quitEventHandler = new QuitEventHandler();

	SDL_Window* m_window;

	ParticleSystem m_particleSystem;
};

