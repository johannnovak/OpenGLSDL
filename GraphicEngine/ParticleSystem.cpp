#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() : m_particleCount(1000), m_updateShader(), m_renderShader(), m_globalTime(0)
{
	m_particles = new Particle[m_particleCount];
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_particles;
}

void ParticleSystem::initialize()
{
	m_updateShader.load("Shaders/particle_update");
	m_updateShader.registerUniform("W");
	m_updateShader.registerUniform("V");
	m_updateShader.registerUniform("P");
	m_updateShader.registerUniform("t");

	m_updateShader.registerAttribute("position");
	m_updateShader.registerAttribute("speed");
	m_updateShader.registerAttribute("color");

	m_updateShader.registerAttribute("spawnTime");
	m_updateShader.registerAttribute("ttl");

	srand(time(NULL));

	for (unsigned int i = 0; i < m_particleCount; ++i)
	{
		initializeParticle(m_particles[i]);
	}
}

float ParticleSystem::prand()
{
	return (float)rand() / (float)RAND_MAX;
}

void ParticleSystem::initializeParticle(Particle& _particle)
{
	_particle.spawnTime = m_globalTime;

	_particle.ttl = (prand() * 1000 - 500) + 2000;

	_particle.x = prand()*7.5f - 7.5f / 2.0f;
	_particle.y = 5.0f;
	_particle.z = prand()*7.5f - 7.5f / 2.0f;

	_particle.dy = - (0.005f * prand());
	_particle.dx = 0; // 0.002f * prand() - 0.001f;
	_particle.dz = 0; // 0.002f * prand() - 0.001f;

	_particle.r = 0;
	_particle.g = 0;
	_particle.b = 1;
}

void ParticleSystem::setView(GLfloat* _view)
{
	m_view = _view;
}

void ParticleSystem::setProjection(GLfloat* _projection)
{
	m_projection = _projection;
}

void ParticleSystem::setWorld(GLfloat* _world)
{
	m_world = _world;
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
	m_updateShader.activate();
	m_updateShader.transmitUniformMat4("W", m_world, GL_FALSE);
	m_updateShader.transmitUniformMat4("V", m_view, GL_FALSE);
	m_updateShader.transmitUniformMat4("P", m_projection, GL_FALSE);

	m_updateShader.transmitUniformFloat("t", m_globalTime);

	GLfloat* particlesToFloat = (float*)m_particles;

	glVertexAttribPointer(m_updateShader.getAttrLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat);
	glVertexAttribPointer(m_updateShader.getAttrLocation("speed"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 3);
	glVertexAttribPointer(m_updateShader.getAttrLocation("color"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 6);

	glVertexAttribPointer(m_updateShader.getAttrLocation("ttl"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 9);
	glVertexAttribPointer(m_updateShader.getAttrLocation("spawnTime"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particlesToFloat + 10);

	m_updateShader.enableAllAttrib();
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, m_particleCount);
	m_updateShader.disableAllAttrib();
}