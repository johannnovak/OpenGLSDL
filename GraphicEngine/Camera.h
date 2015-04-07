#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "SceneNode.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

class Camera
{
public:
	Camera(SceneNode& _node);
	virtual ~Camera();

	void setFOV(float _fov);

	glm::mat4& getView();
	glm::mat4& getProjection();

private:
	void computeMatrices();

private:
	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;

	glm::mat4 m_projection;
	glm::mat4 m_view;

	SceneNode& m_node;
};

