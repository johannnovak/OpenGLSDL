#pragma once

#include <ctime>
#include <random>

#include "Shader.h"

struct Particle 
{
	float x, y, z;		// 0
	float dx, dy, dz;	// 3*sizeof(float) + 0
	float r, g, b;		// 3*sizeof(float) + 3*sizeof(float) + 0

	float ttl;			// 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 0
	float spawnTime;	// sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 0
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void initialize();
	void initializeParticle(Particle& _particle);

	void setView(GLfloat* _view);
	void setProjection(GLfloat* _projection);
	void setWorld(GLfloat* _world);

	float prand();

	void update(float _dt);
	void draw(float _dt);

private:
	unsigned int m_particleCount;
	Shader m_renderShader;
	Shader m_updateShader;

	Particle* m_particles;

	float m_globalTime;

	GLfloat* m_view;
	GLfloat* m_projection;
	GLfloat* m_world;

};

