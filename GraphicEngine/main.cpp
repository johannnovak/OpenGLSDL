#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include <Windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL.h>

#include "SDLEventManager.h"
#include "SDLInputManager.h"

#include "Framework.h"
#include "LogManager.h"
#include "Shader.h"
#include "Camera.h"

using namespace std;

const char* loadFile(string _file);
void draw();
bool initialize();
void exit(SDL_GLContext _context, SDL_Window* _win);

float r = 5.0f, theta = 0;

float ry = 0, rx = 0, rz = 0;

float z = 0, x = 0;

float fov = M_PI / 4.0f;

Shader* cellShader = NULL;
Shader* shader = NULL;
Shader* outline = NULL;

Shader* activeShader = NULL;

Camera* camera = NULL;

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

QuitEventHandler* quitEventHandler = new QuitEventHandler();

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	LogManager::setWindow(win);

	SDL_GLContext mainContext = SDL_GL_CreateContext(win);
	if (mainContext == nullptr)
	{
		cout << "SDL_CreateContext Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	glewInit();

	if (!initialize())
	{
		exit(mainContext, win);
		return EXIT_FAILURE;
	}

	while (!quitEventHandler->m_quit)
	{
		// Handle Events
		SDLEventManager::pollSDLEvents();

		InputManager* inputManager = InputManager::getInstance();
		if (inputManager->isKeyDown(IM_KEY_RIGHT))
			theta += 0.01f;

		if (inputManager->isKeyDown(IM_KEY_LEFT))
			theta -= 0.01f;

		if (inputManager->isKeyDown(IM_KEY_DOWN))
			r += 0.1f;

		if (inputManager->isKeyDown(IM_KEY_UP))
			r -= 0.1f;

		if (inputManager->isKeyDown(IM_KEY_ESCAPE))
			quitEventHandler->externQuit();

		// Update
		camera->setPosition(r * sin(theta), 0, r*cos(theta));
		// camera->setRotation(rx, ry, 0);

		// Draw
		draw();
		SDL_GL_SwapWindow(win);
	}


	exit(mainContext, win);

	return EXIT_SUCCESS;
}

void exit(SDL_GLContext _context, SDL_Window* _win)
{
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_win);

	delete cellShader;
	delete shader;
	delete outline;
	delete camera;

	delete quitEventHandler;

	SDL_Quit();
}

bool initialize()
{
	
	SDLInputManager::initialize();
	SDLEventManager::registerSDLEventHandler((SDLEventHandler*)((SDLInputManager*)SDLInputManager::getInstance()));
	SDLEventManager::registerSDLEventHandler(quitEventHandler);

	glClearColor(0.127f, 0.127f, 0.127f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	cellShader = new Shader("Shaders/cell_shader");
	cellShader->registerUniform("W");
	cellShader->registerUniform("V");
	cellShader->registerUniform("P");
	cellShader->registerUniform("pass");

	cellShader->registerAttribute("position");
	cellShader->registerAttribute("color");
	cellShader->registerAttribute("normal");

	shader = new Shader("Shaders/shader");
	shader->registerUniform("P");
	shader->registerUniform("V");
	shader->registerUniform("W");

	shader->registerAttribute("pos");
	shader->registerAttribute("color");

	outline = new Shader("Shaders/outline");
	outline->registerUniform("P");
	outline->registerUniform("V");
	outline->registerUniform("W");

	outline->registerAttribute("position");
	outline->registerAttribute("normal");

	camera = new Camera();
	camera->setPosition(0, 0, -2);

	return true;
}

void drawAxis()
{
	GLfloat positions[] =
	{
		0, 0, 0,
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
		0, 0, 1,
	};

	GLfloat colors[] =
	{
		1, 0, 0,
		1, 0, 0,
		0, 1, 0,
		0, 1, 0,
		0, 0, 1,
		0, 0, 1,
	};

	shader->activate();

	shader->enableAllAttrib();

	shader->transmitAttrVect3("pos", positions);
	shader->transmitAttrVect3("color", colors);

	glDrawArrays(GL_LINES, 0, 6);
	shader->disableAllAttrib();
}

void drawCircle()
{
	const int def = 100;

	const int size = (def + 2) * 3;
	GLfloat pos[size];
	GLfloat col[size];

	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	col[0] = 0;
	col[1] = 1;
	col[2] = 0;

	double angle = 0;
	for (int i = 3; i < size; i+=3)
	{
		pos[i] = 2*cos(angle);
		pos[i+1] = 2*sin(angle);
		pos[i+2] = 0;

		col[i] = 1;
		col[i+1] = 0;
		col[i+2] = 0;

		angle += 2 * M_PI / def;
	}

	shader->activate();

	shader->transmitAttrVect3("pos", pos);
	shader->transmitAttrVect3("color", col);

	shader->enableAllAttrib();

	glDrawArrays(GL_TRIANGLE_FAN, 0, def+2);

	shader->disableAllAttrib();
}

void drawCube()
{
	float s = 0.5f;
	GLfloat positions[] = {
		-s, -s, s, // Front
		-s, s, s,
		s, -s, s,
		s, s, s,

		s, -s, s, // Right
		s, s, s,
		s, -s, -s,
		s, s, -s,

		s, -s, -s, // Back
		s, s, -s,
		-s, -s, -s,
		-s, s, -s,

		-s, -s, -s, // Left
		-s, s, -s,
		-s, -s, s,
		-s, s, s,

		-s, s, s, // Top
		-s, s, -s,
		s, s, s,
		s, s, -s,

		-s, -s, -s, // Bottom
		-s, -s, s,
		s, -s, -s,
		s, -s, s
	};

	GLfloat colors[] = {
		1, 0, 0, // Front
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,

		0, 1, 0, // Right
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,

		0, 0, 1, // Back
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,

		0.5f, 0.5f, 0, // Left
		0.5f, 0.5f, 0,
		0.5f, 0.5f, 0,
		0.5f, 0.5f, 0,

		0, 0.5f, 0.5f, // Top
		0, 0.5f, 0.5f,
		0, 0.5f, 0.5f,
		0, 0.5f, 0.5f,

		0.5f, 0, 0.5f, // Bottom
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f,
	};

	GLfloat normals[] = {
		-s, -s, s,
		-s, s, s,
		s, -s, s,
		s, s, s,

		0, 0, 0,
		0, 0, 0,
		s, -s, -s,
		s, s, -s,

		0, 0, 0,
		0, 0, 0,
		-s, -s, -s,
		-s, s, -s,
	};

	GLushort indices[] = {
		0, 1, 2, // Front
		1, 2, 3,

		4, 5, 6, // Right
		5, 6, 7,

		8, 9, 10, // Back
		9, 10, 11,

		12, 13, 14, // Left
		13, 14, 15,

		16, 17, 18, // Top
		17, 18, 19,

		20, 21, 22, // Bottom
		21, 22, 23,
	};

	GLushort indicesOutline[] = {
		0, 1, 2,
		2, 1, 3,

		2, 3, 6,
		6, 3, 7,
		
		6, 7, 10,
		10, 7, 11,
		
		10, 11, 0,
		0, 11, 1,
		
		1, 11, 3,
		3, 11, 7,
		
		10, 0, 6,
		6, 0, 2,
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indicesOutline, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);

	/*
	outline->activate();

	outline->transmitAttrVect3("position", positions);
	outline->transmitAttrVect3("normal", normals);

	outline->enableAllAttrib();

	glDisable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
	glEnable(GL_DEPTH_TEST);

	outline->disableAllAttrib();*/

	shader->activate();

	shader->transmitAttrVect3("pos", positions);
	shader->transmitAttrVect3("color", colors);

	shader->enableAllAttrib();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);

	shader->disableAllAttrib();

	glDeleteBuffers(1, &buffer);
}

void drawGround()
{
	GLfloat positions[] = {
		-10, -2, 10,
		-10, -2, -10,
		10, -2, 10,
		10, -2, -10,
	};

	GLfloat colors[] = {
		0.512f, 0.512f, 0.512f,
		0.512f, 0.512f, 0.512f,
		0.512f, 0.512f, 0.512f,
		0.512f, 0.512f, 0.512f,
	};

	shader->activate();

	shader->transmitAttrVect3("pos", positions);
	shader->transmitAttrVect3("color", colors);

	shader->enableAllAttrib();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	shader->disableAllAttrib();
}

void drawPyramide()
{
	int nbSides = 10;
	float rayon = 1.0f;

	if (nbSides > 2)
	{
		float sideNb = 0;
		int size1 = 3 * (nbSides + 2);
		float* positionsTop = new float[size1];
		float* colorsTop = new float[size1];


		for (int i=0; i < size1; i = i + 3)
		{
			if (i == 0){
				positionsTop[0] = 0;
				positionsTop[1] = 0;
				positionsTop[2] = 1;

				colorsTop[0] = 0;
				colorsTop[1] = 1;
				colorsTop[2] = 0;

			}
			else{
				positionsTop[i] = rayon * cos(sideNb * 2 * M_PI / nbSides);
				positionsTop[i + 1] = rayon * sin(sideNb * 2 * M_PI / nbSides);
				positionsTop[i + 2] = 0;

				colorsTop[i + 0] = 1;
				colorsTop[i + 1] = 1;
				colorsTop[i + 2] = 1;

				++sideNb;
			}
		}

		shader->activate();

		shader->transmitAttrVect3("pos", positionsTop);
		shader->transmitAttrVect3("color", colorsTop);


		shader->enableAllAttrib();
		glDrawArrays(GL_TRIANGLE_FAN, 0, nbSides + 2);

		glDrawArrays(GL_TRIANGLE_FAN, 1, nbSides+1);
		shader->disableAllAttrib();

		delete[] positionsTop;
		delete[] colorsTop;
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 World = glm::mat4(1.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(r*cos(theta), 2, r*sin(theta)),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	shader->activate();
	shader->transmitUniformMat4("P", &camera->getProjection()[0][0], GL_FALSE);
	shader->transmitUniformMat4("V", &View[0][0], GL_FALSE);
	shader->transmitUniformMat4("W", &World[0][0], GL_FALSE);

	cellShader->activate();
	cellShader->transmitUniformMat4("P", &camera->getProjection()[0][0], GL_FALSE);
	cellShader->transmitUniformMat4("V", &camera->getView()[0][0], GL_FALSE);
	cellShader->transmitUniformMat4("W", &World[0][0], GL_FALSE);

	outline->activate();
	outline->transmitUniformMat4("P", &camera->getProjection()[0][0], GL_FALSE);
	outline->transmitUniformMat4("V", &camera->getView()[0][0], GL_FALSE);
	outline->transmitUniformMat4("W", &World[0][0], GL_FALSE);

	// drawAxis();
	drawGround();
	drawCube();

	// drawPyramide();

}