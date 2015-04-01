#include "SceneNode.h"


SceneNode::SceneNode() : m_childs(), m_position(), m_rotation(), m_parent(nullptr)
{

}

SceneNode::SceneNode(SceneNode* _parent) : m_childs(), m_position(), m_rotation()
{
	m_parent = _parent;
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
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

glm::mat4 SceneNode::getWorldMatrice()
{
	glm::mat4 result(1);

	glm::mat4 rotX(1), rotY(1), rotZ(1), pos(1);
	
	rotX[0][0] = 1; rotX[0][1] = 0; rotX[0][2] = 0; rotX[0][3] = 0;
	rotX[1][0] = 0; rotX[1][1] = cos(m_rotation.x); rotX[1][2] = -sin(m_rotation.x); rotX[1][3] = 0;
	rotX[2][0] = 0; rotX[2][1] = sin(m_rotation.x); rotX[2][2] = cos(m_rotation.x); rotX[2][3] = 0;
	rotX[3][0] = 0; rotX[3][1] = 0; rotX[3][2] = 0; rotX[3][3] = 1;

	rotY[0][0] = cos(m_rotation.y); rotY[0][1] = 0; rotY[0][2] = sin(m_rotation.y); rotY[0][3] = 0;
	rotY[1][0] = 0; rotY[1][1] = 1; rotY[1][2] = 0; rotY[1][3] = 0;
	rotY[2][0] = -sin(m_rotation.y); rotY[2][1] = 0; rotY[2][2] = cos(m_rotation.y); rotY[2][3] = 0;
	rotY[3][0] = 0; rotY[3][1] = 0; rotY[3][2] = 0; rotY[3][3] = 1;

	rotZ[0][0] = cos(m_rotation.z); rotZ[0][1] = -sin(m_rotation.z); rotZ[0][2] = 0; rotZ[0][3] = 0;
	rotZ[1][0] = sin(m_rotation.z); rotZ[1][1] = cos(m_rotation.z); rotZ[1][2] = 0; rotZ[1][3] = 0;
	rotZ[2][0] = 0; rotZ[2][1] = 0; rotZ[2][2] = 1; rotZ[2][3] = 0;
	rotZ[3][0] = 0; rotZ[3][1] = 0; rotZ[3][2] = 0; rotZ[3][3] = 1;

	pos[0][0] = 1; pos[0][1] = 0; pos[0][2] = 0; pos[0][3] = m_position.x;
	pos[1][0] = 0; pos[1][1] = 1; pos[1][2] = 0; pos[1][3] = m_position.y;
	pos[2][0] = 0; pos[2][1] = 0; pos[2][2] = 1; pos[2][3] = m_position.z;
	pos[3][0] = 0; pos[3][1] = 0; pos[3][2] = 0; pos[3][3] = 1;

	result = rotZ * rotY * rotX * pos;

	return result;
}

Object3D& SceneNode::getObject3D()
{
	return *m_object3d;
}

void SceneNode::setObject3D(Object3D* _object3d)
{
	m_object3d = _object3d;
}