#include "Camera.h"

Camera::Camera(SceneNode& _node) 
: m_projection(1), m_view(1), m_fov(45), m_aspect(640.0f / 480.0f), m_near(0.1f), m_far(1000.0f), m_node(_node)
{
}

Camera::~Camera()
{
}

SceneNode& Camera::getSceneNode()
{
	return m_node;
}

void Camera::setFOV(float _fov)
{
	m_fov = _fov;
}

glm::mat4& Camera::getView()
{
	m_view = glm::transpose(glm::inverse(m_node.computeWorldMatrice()));
	return m_view;
}

glm::mat4& Camera::getProjection()
{
	computeMatrices();
	return m_projection;
}

void Camera::computeMatrices()
{
	m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}