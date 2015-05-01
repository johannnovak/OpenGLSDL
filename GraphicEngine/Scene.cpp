#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

SceneNode& Scene::getRootNode()
{
	return m_rootNode;
}