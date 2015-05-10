#pragma once

#include <chrono>
#include <thread>

class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();

public:
	void go();

protected:
	virtual void initialize() = 0;
	virtual void loadContent() = 0;

	virtual void update(float _dt) = 0;
	virtual void draw(float _dt) = 0;

	virtual void unloadContent() = 0;

private:
	void loop();

protected:
	long m_globalTime;
	unsigned int m_targetFps;
	bool m_quit;

};

