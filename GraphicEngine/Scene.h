#pragma once

#include "SceneNode.h"

class Scene
{
public:
	Scene();
	~Scene();

	SceneNode& getRootNode();

private:
	SceneNode m_rootNode;
};

