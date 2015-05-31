#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : m_particleCount(1000), m_globalTime(0), m_particleSize(5.0f)
{
	
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_particles;
}

void ParticleSystem::initialize()
{
    std::cout << "Initializing ParticleSystem" << std::endl;
	m_shader = ShaderBank::getShader("Shaders/Particle/fade_in_out");

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

	m_particles = new Particle[m_particleCount];
	for (unsigned int i = 0; i < m_particleCount; ++i)
	{
		initializeParticle(m_particles[i]);
	}
}

void ParticleSystem::initializeParticle(Particle& _particle)
{
	_particle.spawnTime = m_globalTime;

	_particle.ttl = (Helpers::prand() * 1000 - 500) + 2000;

	_particle.x = Helpers::prand()*7.5f - 7.5f / 2.0f;
	_particle.y = 5.0f;
	_particle.z = Helpers::prand()*7.5f - 7.5f / 2.0f;

	_particle.dy = -(0.005f * Helpers::prand());
	_particle.dx = 0; // 0.002f * prand() - 0.001f;
	_particle.dz = 0; // 0.002f * prand() - 0.001f;

	_particle.ax = 0;
	_particle.ay = 0;
	_particle.az = 0;

	_particle.r = 0;
	_particle.g = 0;
	_particle.b = 1;
}

void ParticleSystem::update(float _dt)
{
	m_globalTime += _dt;
	// reseting dead particles
	for (unsigned int i = 0; i < m_particleCount; ++i)
	{
		if (m_particles[i].ttl + m_particles[i].spawnTime <= m_globalTime)
			initializeParticle(m_particles[i]);
	}
}

void ParticleSystem::draw(float _dt)
{
	m_shader->activate();
	m_shader->transmitUniformMat4("W", m_world, GL_FALSE);
	m_shader->transmitUniformMat4("V", m_view, GL_FALSE);
	m_shader->transmitUniformMat4("P", m_projection, GL_FALSE);

	m_shader->transmitUniformFloat("t", m_globalTime);
	preDraw(_dt);

	GLfloat* particlesToFloat = (float*)m_particles;

	glVertexAttribPointer(m_shader->getAttrLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 0);
	glVertexAttribPointer(m_shader->getAttrLocation("speed"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 3);
	glVertexAttribPointer(m_shader->getAttrLocation("acceleration"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 6);
	glVertexAttribPointer(m_shader->getAttrLocation("color"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 9);

	glVertexAttribPointer(m_shader->getAttrLocation("ttl"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 12);
	glVertexAttribPointer(m_shader->getAttrLocation("spawnTime"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 13);

	m_shader->enableAllAttrib();
	glPointSize(m_particleSize);
	glDrawArrays(GL_POINTS, 0, m_particleCount);
	m_shader->disableAllAttrib();
}

void ParticleSystem::preDraw(float)
{}
