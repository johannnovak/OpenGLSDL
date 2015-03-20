#include "Camera.h"

Camera::Camera() 
: m_projection(1), m_view(1), m_fov(45), m_aspect(4.0f / 3.0f), m_near(0.1f), m_far(100.0f), m_needRecompute(false), m_rotateTest(0)
{
}


Camera::~Camera()
{
}

void Camera::setFOV(float _fov)
{
	m_fov = _fov;
	m_needRecompute = true;
}

void Camera::setPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_needRecompute = true;
}

void Camera::setRotation(float rx, float ry, float rz)
{
	m_rotation.x = rx;
	m_rotation.y = ry;
	m_rotation.z = rz;

	m_needRecompute = true;
}

glm::mat4& Camera::getView()
{
	computeMatrices();
	return m_view;
}

glm::mat4& Camera::getProjection()
{
	computeMatrices();
	return m_projection;
}

void Camera::computeMatrices()
{
	if (!m_needRecompute)
		return;

	m_view = glm::mat4(1);
	m_view = glm::rotate(m_view, m_rotation.x, glm::vec3(1, 0, 0));
	m_view = glm::rotate(m_view, m_rotation.y, glm::vec3(0, 1, 0));
	m_view = glm::translate(m_view, m_position);
	m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::setRotateTest(float val)
{
	m_rotateTest = val;
}