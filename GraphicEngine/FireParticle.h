#pragma once
#include "ParticleSystem.h"

class FireParticle :
	public ParticleSystem
{
public:
	FireParticle();
	virtual ~FireParticle();

public:
	void initialize();
	void initializeParticle(Particle& _particle);
};

