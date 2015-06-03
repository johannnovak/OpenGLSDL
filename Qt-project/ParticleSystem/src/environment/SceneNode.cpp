#include "SceneNode.h" // Implemented class.

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  SceneNode()
* Description: Default constructor. By default, there is no rotation,
*						the scale is set to 1 and the SceneNode has no
*						parent and contains no object3D.
* Inputs: none
**************************************************************************/
SceneNode::SceneNode() : m_children(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(nullptr), m_object3d(nullptr)
{
}

/**************************************************************************
* Name:  SceneNode(SceneNode* _parent)
* Description: Default constructor. Same as above but sets the 'm_parent'
*						attribute.
* Inputs:
*			- _parent : SceneNode*, parent of the current Node created.
**************************************************************************/
SceneNode::SceneNode(SceneNode* _parent) : m_children(), m_position(), m_rotation(1, 0, 0, 0), m_scale(1, 1, 1), m_parent(_parent), m_object3d(nullptr)
{
}

/**************************************************************************
* Name:  ~SceneNode()
* Description: Default destructor. Deletes all children.
* Inputs: none
**************************************************************************/
SceneNode::~SceneNode()
{
    for (SceneNode* node : m_children)
    {
        delete node;
    }
    m_children.clear();
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: setPosition(float32 _x, float32 _y, float32 _z)
* Description: Setter for the 'm_position' attribute.
* Inputs: none
*			- _x : float32, x coordinate of the position.
*			- _y : float32, y coordinate of the position.
*			- _z : float32, z coordinate of the position.
* Returns: none
**************************************************************************/
void SceneNode::setPosition(float32 _x, float32 _y, float32 _z)
{
    m_position.x = _x;
    m_position.y = _y;
    m_position.z = _z;
}

/**************************************************************************
* Name: setRotation(float32 _x, float32 _y, float32 _z)
* Description: Setter for the 'm_rotation' attribute.
* Inputs:
*			- _x : float32, x coordinate of the quaternion rotation.
*			- _y : float32, y coordinate of the quaternion rotation.
*			- _z : float32, z coordinate of the quaternion rotation.
* Returns: none
**************************************************************************/
void SceneNode::setRotation(float32 _x, float32 _y, float32 _z)
{
    Quaternion::computeRotationQuaternion(_x, _y, _z, m_rotation);
}

/**************************************************************************
* Name: setScale(float32 _x, float32 _y, float32 _z)
* Description: Setter for the 'm_scale' attribute.
* Inputs:
*			- _x : float32, x factor of the scaling vector.
*			- _y : float32, y factor of the scaling vector.
*			- _z : float32, z factor of the scaling vector.
* Returns: none
**************************************************************************/
void SceneNode::setScale(float32 _x, float32 _y, float32 _z)
{
    m_scale.x = _x;
    m_scale.y = _y;
    m_scale.z = _z;
}

/**************************************************************************
* Name: setObject3D(Object3D _object3d)
* Description: Setter for the 'm_object3d' attribute.
* Inputs:
*			- _object3d : Object3D*, pointer on the SceneNode's Object3D.
* Returns: none
**************************************************************************/
void SceneNode::setObject3D(Object3D* _object3d)
{
    m_object3d = _object3d;
}

/**************************************************************************
* Name: getRotation()
* Description: Getter for the 'm_rotation' attribute.
* Inputs: none
* Returns:
*			- m_rotation : Rotation Matrix attribute of the SceneNode.
**************************************************************************/
const Quaternion& SceneNode::getRotation() const
{
    return m_rotation;
}

/**************************************************************************
* Name: getPosition()
* Description: Getter for the 'm_position' attribute.
* Inputs: none
* Returns:
*			- m_position: Position vector of the SceneNode.
**************************************************************************/
const glm::vec3& SceneNode::getPosition() const
{
    return m_position;
}

/**************************************************************************
* Name: getChildren()
* Description: Getter for the 'm_childs' attribute.
* Inputs: none
* Returns:
*			- m_children: LinkedList of the SceneNode children.
**************************************************************************/
std::list<SceneNode*>& SceneNode::getChildren()
{
    return m_children;
}

/**************************************************************************
* Name: getParent()
* Description: Getter for the 'm_parent' attribute.
* Inputs: none
* Returns:
*			- m_parent: parent SceneNode.
**************************************************************************/
SceneNode* SceneNode::getParent()
{
    return m_parent;
}

/**************************************************************************
* Name: getObject3D()
* Description: Getter for the 'm_object3d' attribute.
* Inputs: none
* Returns:
*			- m_object3d: Object3D that possesses the current SceneNode.
**************************************************************************/
Object3D& SceneNode::getObject3D()
{
    return *m_object3d;
}

//============================= INQUIRY ===========================================

/**************************************************************************
* Name: hasObject3D()
* Description: Inquirer of the value of the 'm_object3d' attribute.
* Inputs: none
* Returns:
*			- True if 'm_object3d' is not a nullptr;
*			- False otherwise.
**************************************************************************/
bool SceneNode::hasObject3D()
{
    return m_object3d != nullptr;
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: rotate(float32 _angle, glm::vec3 _axis)
* Description: Apply a rotation to the rotation matrix 'm_rotation' biased on
*					the parameter '_axis' with an angle of '_angle'.
* Inputs:
*			- _angle : float32, angle of the rotation to apply.
*			- _axis  : glm::vec3, axis of the rotation to apply.
* Returns: none
**************************************************************************/
void SceneNode::rotate(float32 _angle, glm::vec3 _axis)
{
    m_rotation.rotate(_angle, _axis);
}

/**************************************************************************
* Name: translate(const glm::vec3& _vect)
* Description: Adds the translation vector to the 'm_position' vector :
*						translates the position.
* Inputs:
*			- _vect  : const glm::vec3&, vector to add to the position to
*							translate the SceneNode.
* Returns: none
**************************************************************************/
void SceneNode::translate(const glm::vec3& _vect)
{
    m_position += _vect;
}

/**************************************************************************
* Name: translate(float32 _dx, float32 _dy, float32 _dz)
* Description: Adds the translation coordinates to each of the 'm_position'
*						vector coordinates in order to perform  the translation.
* Inputs:
*			- _dx : float32, x coordinate to add to the position.
*			- _dy : float32, y coordinate to add to the position.
*			- _dz : float32, z coordinate to add to the position.
* Returns: none
**************************************************************************/
void SceneNode::translate(float _dx, float _dy, float _dz)
{
    m_position.x += _dx;
    m_position.y += _dy;
    m_position.z += _dz;
}

/**************************************************************************
* Name: computeWorldMatrix(float32 _dx, float32 _dy, float32 _dz)
* Description: Method used to compute the World Matrix. First the rotation
*						matrix and the position are merged inside one new matrix,
*						then this one is multiplied by its parent World matrix
*						obtained through a recursive call of this method.
* Inputs: none
* Returns:
*			- result : glm::mat4, World Matrix.
**************************************************************************/
glm::mat4 SceneNode::computeWorldMatrix()
{
    /* Merges the rotation matrix with the position. */
    glm::mat4 result = (glm::mat4) m_rotation;

    result[0][3] = m_position.x;
    result[1][3] = m_position.y;
    result[2][3] = m_position.z;

    /* Multiplies with parent's world matrix and returns it. */
    if (m_parent != nullptr)
        return result * m_parent->computeWorldMatrix();
    else
        return result;
}

/**************************************************************************
* Name: computeGlobalPosition()
* Description: Method used to compute the global Position of the SceneNode.
*						Multiplies recursively the current position vector with
*						the parent World Matrix.
* Inputs: none
* Returns:
*			- glm::vec3 : Global position of the SceneNode.
**************************************************************************/
glm::vec3 SceneNode::computeGlobalPosition() const
{
    glm::vec4 pos = glm::vec4(m_position, 1.0f);
    if (m_parent != nullptr)
        pos = m_parent->computeWorldMatrix() * pos;

    return glm::vec3(pos.x, pos.y, pos.z);
}

/**************************************************************************
* Name:  addChild(SceneNode* _child)
* Description: Method used to add a child SceneNode to the LinkedList
*						'm_children'.
* Inputs:
*			- _child : SceneNode*, SceneNode to be added to 'm_children'.
* Returns: none
**************************************************************************/
void SceneNode::addChild(SceneNode* _child)
{
    m_children.push_back(_child);
}

/**************************************************************************
* Name:  removeChild(SceneNode* _child)
* Description: Method used to remove a child SceneNode from the LinkedList
*						'm_children'.
* Inputs:
*			- _child : SceneNode*, SceneNode to be removed from 'm_children'.
* Returns: none
**************************************************************************/
void SceneNode::removeChild(SceneNode* _child)
{
    m_children.remove(_child);
}

