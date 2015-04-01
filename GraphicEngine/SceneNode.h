#pragma once

#include <list>
#include <glm/glm.hpp>
#include <cmath>

#include "Object3D.h"

class SceneNode
{
public:
	SceneNode();
	SceneNode(SceneNode* _parent);
	~SceneNode();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	glm::mat4 getWorldMatrice();

	void addChild(SceneNode* _child);
	void removeChild(SceneNode* _child);

	std::list<SceneNode*>& getChilds();
	SceneNode* getParent();

	Object3D& getObject3D();
	void setObject3D(Object3D* _object3d);

private:
	SceneNode* m_parent;
	std::list<SceneNode*> m_childs;

	glm::vec3 m_rotation;
	glm::vec3 m_position;

	Object3D* m_object3d;
};

