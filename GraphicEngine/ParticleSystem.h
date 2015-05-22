#pragma once

#include <ctime>
#include <random>

#include "Helpers.h"

#include "AbstractParticleSystem.h"
#include "Shader.h"
#include "ShaderBank.h"

class ParticleSystem : public AbstractParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

public:
	virtual void initialize();
	virtual void initializeParticle(Particle& _particle);

	void update(float _dt);
	void draw(float _dt);

protected:
	virtual void preDraw(float _dt);

protected:
	unsigned int m_particleCount;
	float m_particleSize;

	float m_globalTime;
};

