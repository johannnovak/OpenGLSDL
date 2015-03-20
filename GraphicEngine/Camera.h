#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void setFOV(float _fov);

	void setPosition(float x, float y, float z);
	void setRotation(float rx, float ry, float rz);

	void setRotateTest(float val);

	glm::mat4& getView();
	glm::mat4& getProjection();

private:
	void computeMatrices();

private:
	bool m_needRecompute;

	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;

	glm::vec3 m_position;
	glm::vec3 m_rotation;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_rotateTest;


};

