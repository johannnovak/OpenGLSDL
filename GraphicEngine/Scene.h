#pragma once

#include "SceneNode.h"

class Scene
{
public:
	Scene();
	~Scene();

	static Scene& getInstance();

	SceneNode& getRootNode();
	void destroy();

private:
	static Scene* s_instance;

	SceneNode m_rootNode;
};

