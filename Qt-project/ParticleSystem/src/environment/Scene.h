#ifndef SCENE_H
#define SCENE_H

#include <SceneNode.h>

class Scene
{
public:
	Scene();
	~Scene();

	SceneNode* getRootNode();

private:
	SceneNode* m_rootNode;
};

#endif
