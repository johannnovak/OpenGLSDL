#pragma once
#include "ParticleSystem.h"

class AtmosphericParticleSystem : public ParticleSystem
{
public:
	AtmosphericParticleSystem();
	virtual ~AtmosphericParticleSystem();

protected:
	virtual void initializeParticle(Particle& _particle);
};

