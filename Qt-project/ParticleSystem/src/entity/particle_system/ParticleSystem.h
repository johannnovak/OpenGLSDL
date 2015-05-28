#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "AbstractParticleSystem.h"
#include "ShaderBank.h"
#include "Helpers.h"

#include <ctime>
#include <random>

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

#endif
