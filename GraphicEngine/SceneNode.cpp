#include "SceneNode.h"


SceneNode::SceneNode() : m_childs(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(nullptr), m_object3d(nullptr)
{
}

SceneNode::SceneNode(SceneNode* _parent) : m_childs(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(_parent), m_object3d(nullptr)
{
}


SceneNode::~SceneNode()
{
	for (SceneNode* node : m_childs)
	{
		delete node;
	}
	m_childs.clear();
}

void SceneNode::addChild(SceneNode* _child)
{
	m_childs.push_back(_child);
}

void SceneNode::removeChild(SceneNode* _child)
{
	m_childs.remove(_child);
}

std::list<SceneNode*>& SceneNode::getChilds()
{
	return m_childs;
}

const glm::vec3& SceneNode::getPosition() const
{
	return m_position;
}

SceneNode* SceneNode::getParent()
{
	return m_parent;
}

const Quaternion& SceneNode::getRotation() const
{
	return m_rotation;
}

void SceneNode::setPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void SceneNode::setRotation(float x, float y, float z)
{
	Quaternion::computeRotationQuaternion(x, y, z, m_rotation);
}

void SceneNode::rotate(float _angle, glm::vec3& _axis)
{
	m_rotation.rotate(_angle, _axis);
}

void SceneNode::translate(float _dx, float _dy, float _dz)
{
	m_position.x += _dx;
	m_position.y += _dy;
	m_position.z += _dz;
}

void SceneNode::translate(const glm::vec3& _vect)
{
	m_position += _vect;
}

void SceneNode::setScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

glm::mat4 SceneNode::computeWorldMatrice()
{
	glm::mat4 result = (glm::mat4) m_rotation;

	result[0][3] = m_position.x;
	result[1][3] = m_position.y;
	result[2][3] = m_position.z;

	if (m_parent != nullptr)
		return result * m_parent->computeWorldMatrice();
	else 
		return result;
}

glm::vec3 SceneNode::computeGlobalPosition() const
{
	glm::vec4 pos = glm::vec4(m_position, 1.0f);
	if (m_parent != nullptr)
		pos = m_parent->computeWorldMatrice() * pos;

	return glm::vec3(pos.x, pos.y, pos.z);
}

Object3D& SceneNode::getObject3D()
{
	return *m_object3d;
}

void SceneNode::setObject3D(Object3D* _object3d)
{
	m_object3d = _object3d;
}

bool SceneNode::hasObject3D()
{
	return m_object3d != nullptr;
}