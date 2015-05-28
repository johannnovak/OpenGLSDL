#include "GraphicEngine.h"

//------------------------------------------------
GraphicEngine::GraphicEngine()
{
}

//------------------------------------------------
GraphicEngine::~GraphicEngine()
{
}

//------------------------------------------------
void GraphicEngine::setShader(Shader* _shader)
{
	m_currentShader = _shader;
}

//------------------------------------------------
void GraphicEngine::drawObject3D(Object3D& _object)
{
	m_currentShader->activate();

	m_currentShader->transmitAttrVect3(ShaderAttributeType_POSITION, _object.getVertices());
	
	if (m_currentShader->getAttrLocation(ShaderAttributeType_COLOR) != -1 && _object.defineColors())
		m_currentShader->transmitAttrVect3(ShaderAttributeType_COLOR, _object.getColors());
	
	if (m_currentShader->getAttrLocation(ShaderAttributeType_NORMAL) != -1 && _object.defineNormals())
		m_currentShader->transmitAttrVect3(ShaderAttributeType_NORMAL, _object.getNormals());

	if (m_currentShader->getAttrLocation(ShaderAttributeType_UV) != -1 && _object.defineUVs())
		m_currentShader->transmitAttrVect3(ShaderAttributeType_UV, _object.getUVs());

	m_currentShader->enableAllAttrib();

	glDrawElements(GL_TRIANGLES, _object.getIndiceCount(), GL_UNSIGNED_SHORT, _object.getIndices());

	m_currentShader->disableAllAttrib();
}

//------------------------------------------------
void GraphicEngine::drawSceneNode(SceneNode& _node)
{
	if (_node.hasObject3D())
	{
		m_currentShader->activate();

		m_currentShader->transmitUniformMat4(ShaderUniformType_WORLD, &_node.computeWorldMatrice()[0][0]);
		drawObject3D(_node.getObject3D());
	}
}

//------------------------------------------------
void GraphicEngine::drawSceneNode(SceneNode& _node, const glm::mat4& _world)
{
	glm::mat4 nodeWorld = (glm::mat4) _node.getRotation();
	nodeWorld[0][3] = _node.getPosition().x;
	nodeWorld[1][3] = _node.getPosition().y;
	nodeWorld[2][3] = _node.getPosition().z;

	glm::mat4 w = nodeWorld * _world;

	if (_node.hasObject3D())
	{
		m_currentShader->activate();

		m_currentShader->transmitUniformMat4(ShaderUniformType_WORLD, &w[0][0]);
		drawObject3D(_node.getObject3D());
	}

	for (auto node : _node.getChilds())
	{
		drawSceneNode(*node, w);
	}
}

//------------------------------------------------
void GraphicEngine::drawScene(Scene& _scene)
{
	drawSceneNode(*_scene.getRootNode(), glm::mat4(1));
}