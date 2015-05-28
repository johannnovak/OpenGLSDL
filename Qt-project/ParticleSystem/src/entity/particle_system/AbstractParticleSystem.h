#ifndef ABSTRACTPARTICLESYSTEM_H
#define ABSTRACTPARTICLESYSTEM_H

#include "Shader.h"

struct Particle
{
	float x, y, z;		// 0													
	float dx, dy, dz;	// 3*sizeof(float) + 0
	float ax, ay, az;   // 3*sizeof(float + 3*sizeof(float) + 0
	float r, g, b;		// 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 0

	float ttl;			// 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 0
	float spawnTime;	// sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 3*sizeof(float) + 0
};

class AbstractParticleSystem
{
public:
	AbstractParticleSystem();
	virtual ~AbstractParticleSystem();

public:
	void setView(GLfloat* _view);
	void setProjection(GLfloat* _projection);
	void setWorld(GLfloat* _world);
	void setMatrices(GLfloat* _world, GLfloat* _view, GLfloat* _projection);

	virtual void initialize() = 0;
	
	virtual void update(float _dt) = 0;
	virtual void draw(float _dt) = 0;

protected:
	virtual void preDraw(float _dt) = 0;

protected:
	GLfloat* m_view;
	GLfloat* m_projection;
	GLfloat* m_world;

	unsigned int m_particleCount;
	Particle* m_particles;
	Shader* m_shader;

};

#endif
