#include "FireParticle.h"


FireParticle::FireParticle()
{
}


FireParticle::~FireParticle()
{
}

void FireParticle::initialize()
{
	m_shader = ShaderBank::getShader("Shaders/Particle/fire");

	m_shader->registerUniform("W");
	m_shader->registerUniform("V");
	m_shader->registerUniform("P");
	m_shader->registerUniform("t");

	m_shader->registerAttribute("position");
	m_shader->registerAttribute("speed");
	m_shader->registerAttribute("acceleration");
	m_shader->registerAttribute("color");

	m_shader->registerAttribute("spawnTime");
	m_shader->registerAttribute("ttl");

	srand(time(NULL));

	m_particles = new Particle[m_particleCount];
	for (unsigned int i = 0; i < m_particleCount; ++i)
	{
		initializeParticle(m_particles[i]);
	}
}

void FireParticle::initializeParticle(Particle& _particle)
{
	_particle.x = 0;
	_particle.y = 0;
	_particle.z = 0;

	float speed = Helpers::prand() * 0.002f - 0.001f;
	float perc = Helpers::prand();
	_particle.dx = speed * perc;
	_particle.dy = 0;
	_particle.dz = speed * (1-perc);

	_particle.ax = 0;
	_particle.ay = 0.000005f;
	_particle.az = 0;

	_particle.r = 1.0f;
	_particle.g = 0.0f;
	_particle.b = 0.0f;

	_particle.spawnTime = m_globalTime;
	_particle.ttl = Helpers::prand() * 1000.0f + 500.0f;

}
