#pragma once

#include "Shader.h"
#include "Object3D.h"
#include "SceneNode.h"
#include "Scene.h"

class GraphicEngine
{
public:
	GraphicEngine();
	virtual ~GraphicEngine();

public:
	void drawObject3D(Object3D& _object);
	void drawSceneNode(SceneNode& _node);
	void drawScene(Scene& _scene);

private:
	Shader* m_currentShader;
};

