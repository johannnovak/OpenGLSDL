#include "Scene.h"

Scene::Scene() : m_rootNode(new SceneNode())
{
}

Scene::~Scene()
{
}

SceneNode* Scene::getRootNode()
{
	return m_rootNode;
}