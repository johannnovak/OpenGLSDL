#include "SceneNode.h"


SceneNode::SceneNode() : m_childs(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(nullptr)
{

}

SceneNode::SceneNode(SceneNode* _parent) : m_childs(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(_parent)
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

const glm::vec3& SceneNode::getPosition()
{
	return m_position;
}

SceneNode* SceneNode::getParent()
{
	return m_parent;
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

void SceneNode::setScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

glm::mat4 SceneNode::computeWorldMatrice()
{
	glm::mat4 result = (glm::mat4) m_rotation;
	glm::vec3 position = computeGlobalPosition();

	result[0][3] = position.x;
	result[1][3] = position.y;
	result[2][3] = position.z;

	return result;
}

glm::vec3 SceneNode::computeGlobalPosition() const
{
	glm::vec3 pos = m_position;
	if (m_parent != nullptr)
		pos += m_parent->computeGlobalPosition();

	return pos;
}

Object3D& SceneNode::getObject3D()
{
	return *m_object3d;
}

void SceneNode::setObject3D(Object3D* _object3d)
{
	m_object3d = _object3d;
}