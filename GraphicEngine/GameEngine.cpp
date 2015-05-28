#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine() : m_targetFps(60), m_globalTime(0), m_quit(false)
{
}


GameEngine::~GameEngine()
{
}


void GameEngine::go()
{
	initialize();
	loadContent();
	loop();
}

void GameEngine::loop()
{
	float dt = 0.0f;
	long targetTPF = (long) (1.0 / (double)m_targetFps * 1000.0); // time per frame

	while (!m_quit)
	{
		auto start = chrono::high_resolution_clock::now();

		m_globalTime += dt;
		update(dt);
		draw(dt);

		auto dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
		if (dur.count() < targetTPF)
			this_thread::sleep_for(chrono::milliseconds(targetTPF - dur.count()));

		dt = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
	}

	unloadContent();
}