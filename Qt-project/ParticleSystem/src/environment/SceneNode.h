#ifndef SCENENODE_H
#define SCENENODE_H

#include <list>
#include "glm/glm.hpp"
#include <cmath>

#include <Object3D.h>
#include <Quaternion.h>

class SceneNode
{
public:
	SceneNode();
	SceneNode(SceneNode* _parent);
	~SceneNode();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

    void rotate(float _angle, glm::vec3 _axis);
	void translate(const glm::vec3& _vect);
	void translate(float _dx, float _dy, float _dz);

	glm::mat4 computeWorldMatrice();

	const Quaternion& getRotation() const;

	const glm::vec3& getPosition() const;
	glm::vec3 computeGlobalPosition() const;

	void addChild(SceneNode* _child);
	void removeChild(SceneNode* _child);

	std::list<SceneNode*>& getChilds();
	SceneNode* getParent();

	Object3D& getObject3D();
	void setObject3D(Object3D* _object3d);
	bool hasObject3D();


private:
	SceneNode* m_parent;
	std::list<SceneNode*> m_childs;

	Quaternion m_rotation;
	glm::vec3 m_position;
	glm::vec3 m_scale;

	Object3D* m_object3d;
};

#endif
