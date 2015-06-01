#pragma once

#include <glm/glm.hpp>

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

	void setShader(Shader* _shader);

private:
	void drawSceneNode(SceneNode& _node, const glm::mat4& _world);

private:
	Shader* m_currentShader;
};

