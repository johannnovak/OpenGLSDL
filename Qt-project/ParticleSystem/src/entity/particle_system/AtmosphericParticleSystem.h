#ifndef ATMOSPHERICPARTICLESYSTEM_H
#define ATMOSPHERICPARTICLESYSTEM_H

#include "ParticleSystem.h"

class AtmosphericParticleSystem : public ParticleSystem
{
public:
	AtmosphericParticleSystem();
	virtual ~AtmosphericParticleSystem();

protected:
	virtual void initializeParticle(Particle& _particle);
};

#endif
