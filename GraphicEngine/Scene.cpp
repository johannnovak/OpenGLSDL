#include "Scene.h"

Scene* Scene::s_instance = nullptr;

Scene::Scene()
{
}

Scene::~Scene()
{
}

Scene& Scene::getInstance()
{
	if (s_instance == nullptr)
		s_instance = new Scene();

	return *s_instance;
}

void Scene::destroy()
{
	delete s_instance;
	s_instance = nullptr;
}