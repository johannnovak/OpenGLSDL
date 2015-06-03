#include "GraphicEngine.h" // Implemented Class.

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================


/**************************************************************************
* Name:  GraphicEngine()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
GraphicEngine::GraphicEngine()
{
}

/**************************************************************************
* Name:  ~GraphicEngine()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
GraphicEngine::~GraphicEngine()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: setShader(Shader* _shader)
* Description: Setter for the 'm_currentShader' attribute.
* Inputs: none
*			- _shader : Shader*, pointer on the current shader to use.
* Returns: none
**************************************************************************/
void GraphicEngine::setShader(Shader* _shader)
{
    m_currentShader = _shader;
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: drawObject3D(Object3D& _object)
* Description: Draws an Object3D.
* Inputs:
*			- _object : Object3D&, reference on the Object3D to draw in the scene.
* Returns: none
**************************************************************************/
void GraphicEngine::drawObject3D(Object3D& _object)
{
    /* Activate shader (useGLProgram). */
    m_currentShader->activate();

    /* Transmits the position of the object. */
    m_currentShader->transmitAttrVect3(ShaderAttributeType_POSITION, _object.getVertices());

    /* Transmits its colors if it has got any. */
    if (m_currentShader->getAttrLocation(ShaderAttributeType_COLOR) != -1 && _object.defineColors())
        m_currentShader->transmitAttrVect3(ShaderAttributeType_COLOR, _object.getColors());

    /* Transmits its normal vector if it has got any. */
    if (m_currentShader->getAttrLocation(ShaderAttributeType_NORMAL) != -1 && _object.defineNormals())
        m_currentShader->transmitAttrVect3(ShaderAttributeType_NORMAL, _object.getNormals());

    /* Transmits its UV vector if it has got any. */
    if (m_currentShader->getAttrLocation(ShaderAttributeType_UV) != -1 && _object.defineUVs())
        m_currentShader->transmitAttrVect3(ShaderAttributeType_UV, _object.getUVs());

    /* Enable all shader's attributes */
    m_currentShader->enableAllAttrib();

    /* Draw the object through its vertices. */
    glDrawElements(GL_TRIANGLES, _object.getIndiceCount(), GL_UNSIGNED_SHORT, _object.getIndices());

    /* Disable all shader's attributes */
    m_currentShader->disableAllAttrib();
}

/**************************************************************************
* Name: drawSceneNode(SceneNode& _node)
* Description: Draws a SceneNode and its associated Object3D (with drawObject3D).
* Inputs:
*			- _node : SceneNode&, Node of the Scene to draw.
* Returns: none
**************************************************************************/
void GraphicEngine::drawSceneNode(SceneNode& _node)
{
    /* If the node possesses an Object3D. */
    if (_node.hasObject3D())
    {
        /* Activates the current shader. */
        m_currentShader->activate();

        /* Transmits the World Matrix to the shader. */
        m_currentShader->transmitUniformMat4(ShaderUniformType_WORLD, &_node.computeWorldMatrix()[0][0]);

        /* Draws the Object3D. */
        drawObject3D(_node.getObject3D());
    }
}

/**************************************************************************
* Name: drawScene(Scene& _scene)
* Description: Draws the entire Scene from the root SceneNode.
* Inputs:
*			- _scene : Scene&, Scene to draw.
* Returns: none
**************************************************************************/
void GraphicEngine::drawScene(Scene& _scene)
{
    drawSceneNode(*_scene.getRootNode(), glm::mat4(1));
}

/////////////////////////////// PRIVATE ///////////////////////////////////

/**************************************************************************
* Name: drawSceneNode(SceneNode& _node, const glm::mat4& world)
* Description: Draws a SceneNode and its associated Object3D (with drawObject3D).
*						It then calls drawSceneNode for all of its children (recursive).
* Inputs:
*			- _node  : SceneNode&, Node of the Scene to draw.
*			- _world : const glm::mat4&, World Matrix, used to draw the children.
* Returns: none
**************************************************************************/
void GraphicEngine::drawSceneNode(SceneNode& _node, const glm::mat4& _world)
{
    /* Gets the rotation matrix and merges it with the position vector. */
    glm::mat4 nodeWorld = (glm::mat4) _node.getRotation();
    nodeWorld[0][3] = _node.getPosition().x;
    nodeWorld[1][3] = _node.getPosition().y;
    nodeWorld[2][3] = _node.getPosition().z;

    /* Computes the new World Matrix : newW = mergeMatrix*parentWorldMatrix. */
    glm::mat4 w = nodeWorld * _world;

    /* If the Scenenode contains an Object3D. */
    if (_node.hasObject3D())
    {
        /* Activates the shader.: */
        m_currentShader->activate();

        /* Transmits the newly created world matrix to the shader. */
        m_currentShader->transmitUniformMat4(ShaderUniformType_WORLD, &w[0][0]);

        /* Draws the Object3D. */
        drawObject3D(_node.getObject3D());
    }

    /* Draws all children. */
    for (auto node : _node.getChildren())
    {
        drawSceneNode(*node, w);
    }
}
