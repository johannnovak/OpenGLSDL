#include "AtmosphericParticleSystem.h"


AtmosphericParticleSystem::AtmosphericParticleSystem()
{
	// Inherited
	this->m_particleCount = 1000;
	this->m_particleSize = 1.0f;
}


AtmosphericParticleSystem::~AtmosphericParticleSystem()
{
}

void AtmosphericParticleSystem::initializeParticle(Particle& _particle)
{
	_particle.spawnTime = m_globalTime;

	_particle.ttl = 10000 + (Helpers::prand() * 3000.0f - 1500.0f);

	float r = Helpers::prand() * 100.0f;
	float angle1 = Helpers::prand() * 2 * M_PI - M_PI;
	float angle2 = Helpers::prand() * 2 * M_PI - M_PI;

	_particle.x = cosf(angle1)*sinf(angle2)*r;
	_particle.y = sinf(angle1)*sinf(angle2)*r + 2.0f;
	_particle.z = cosf(angle2) * r;

	_particle.dy = 0;
	_particle.dx = 0;
	_particle.dz = 0;

	_particle.r = 0.803f;
	_particle.g = 0.522f;
	_particle.b = 0.257f;
}