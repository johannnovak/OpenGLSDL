#include "AbstractParticleSystem.h"


AbstractParticleSystem::AbstractParticleSystem()
{
}


AbstractParticleSystem::~AbstractParticleSystem()
{
}

void AbstractParticleSystem::setView(GLfloat* _view)
{
	m_view = _view;
}

void AbstractParticleSystem::setProjection(GLfloat* _projection)
{
	m_projection = _projection;
}

void AbstractParticleSystem::setWorld(GLfloat* _world)
{
	m_world = _world;
}

void AbstractParticleSystem::setMatrices(GLfloat* _world, GLfloat* _view, GLfloat* _projection)
{
	setWorld(_world);
	setView(_view);
	setProjection(_projection);
}
