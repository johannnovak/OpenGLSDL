#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "Object3D.h"
#include "Quaternion.h"

#include "glm/glm.hpp"
#include <list>
#include <cmath>

/**************************************************************************
* Class: SceneNode
* Description: Class designed to represent a Node in the Scene. The Node is
*						used as an advanced way of "pushing" and "popping" OpenGL
*						matrices. Each Node contains 0 to N Nodes and have their
*						own local position and their own rotate/scale ratios
*						independant from the rest of the World.
*
**************************************************************************/
class SceneNode
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* LinkedList of SceneNode representing its children. */
        std::list<SceneNode*> m_children;

        /* Local position of the SceneNode. */
        glm::vec3 m_position;

        /* Quaternion associated with its current rotation. */
        Quaternion m_rotation;

        /* 3-component vector representing itsd scaling factors. */
        glm::vec3 m_scale;

        /* Parent of the SceneNode. */
        SceneNode* m_parent;

        /* 3D object contained by the SceneNode. */
        Object3D* m_object3d;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  SceneNode()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        SceneNode();

        /**************************************************************************
        * Name:  SceneNode(SceneNode* _parent)
        * Description: Default constructor.
        * Inputs:
        *			- _parent : SceneNode*, parent of the current Node created.
        **************************************************************************/
        SceneNode(SceneNode* _parent);

        /**************************************************************************
        * Name:  ~SceneNode()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        ~SceneNode();

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
        void setPosition(float32 _x, float32 _y, float32 _z);

        /**************************************************************************
        * Name: setRotation(float32 _x, float32 _y, float32 _z)
        * Description: Setter for the 'm_rotation' attribute.
        * Inputs:
        *			- _x : float32, x coordinate of the quaternion rotation.
        *			- _y : float32, y coordinate of the quaternion rotation.
        *			- _z : float32, z coordinate of the quaternion rotation.
        * Returns: none
        **************************************************************************/
        void setRotation(float32 _x, float32 _y, float32 _z);

        /**************************************************************************
        * Name: setScale(float32 _x, float32 _y, float32 _z)
        * Description: Setter for the 'm_scale' attribute.
        * Inputs:
        *			- _x : float32, x factor of the scaling vector.
        *			- _y : float32, y factor of the scaling vector.
        *			- _z : float32, z factor of the scaling vector.
        * Returns: none
        **************************************************************************/
        void setScale(float32 _x, float32 _y, float32 _z);

        /**************************************************************************
        * Name: setObject3D(Object3D _object3d)
        * Description: Setter for the 'm_object3d' attribute.
        * Inputs:
        *			- _object3d : Object3D*, pointer on the SceneNode's Object3D.
        * Returns: none
        **************************************************************************/
        void setObject3D(Object3D* _object3d);

        /**************************************************************************
        * Name: getRotation()
        * Description: Getter for the 'm_rotation' attribute.
        * Inputs: none
        * Returns:
        *			- m_rotation : Rotation Matrix attribute of the SceneNode.
        **************************************************************************/
        const Quaternion& getRotation() const;

        /**************************************************************************
        * Name: getPosition()
        * Description: Getter for the 'm_position' attribute.
        * Inputs: none
        * Returns:
        *			- m_position: Position vector of the SceneNode.
        **************************************************************************/
        const glm::vec3& getPosition() const;

        /**************************************************************************
        * Name: getChildren()
        * Description: Getter for the 'm_childs' attribute.
        * Inputs: none
        * Returns:
        *			- m_children: LinkedList of the SceneNode children.
        **************************************************************************/
        std::list<SceneNode*>& getChildren();

        /**************************************************************************
        * Name: getParent()
        * Description: Getter for the 'm_parent' attribute.
        * Inputs: none
        * Returns:
        *			- m_parent: parent SceneNode.
        **************************************************************************/
        SceneNode* getParent();

        /**************************************************************************
        * Name: getObject3D()
        * Description: Getter for the 'm_object3d' attribute.
        * Inputs: none
        * Returns:
        *			- m_object3d: Object3D that possesses the current SceneNode.
        **************************************************************************/
        Object3D& getObject3D();

    //============================= INQUIRY ============================================

        /**************************************************************************
        * Name: hasObject3D()
        * Description: Inquirer of the value of the 'm_object3d' attribute.
        * Inputs: none
        * Returns:
        *			- True if 'm_object3d' is not a nullptr;
        *			- False otherwise.
        **************************************************************************/
        bool hasObject3D();

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
        void rotate(float32 _angle, glm::vec3 _axis);

        /**************************************************************************
        * Name: translate(const glm::vec3& _vect)
        * Description: Adds the translation vector to the 'm_position' vector :
        *						translates the position.
        * Inputs:
        *			- _vect  : const glm::vec3&, vector to add to the position to
        *							translate the SceneNode.
        * Returns: none
        **************************************************************************/
        void translate(const glm::vec3& _vect);

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
        void translate(float32 _dx, float32 _dy, float32 _dz);

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
        glm::mat4 computeWorldMatrix();

        /**************************************************************************
        * Name: computeGlobalPosition()
        * Description: Method used to compute the global Position of the SceneNode.
        *						Multiplies recursively the current position vector with
        *						the parent World Matrix.
        * Inputs: none
        * Returns:
        *			- glm::vec3 : Global position of the SceneNode.
        **************************************************************************/
        glm::vec3 computeGlobalPosition() const;

        /**************************************************************************
        * Name:  addChild(SceneNode* _child)
        * Description: Method used to add a child SceneNode to the LinkedList
        *						'm_children'.
        * Inputs:
        *			- _child : SceneNode*, SceneNode to be added to 'm_children'.
        * Returns: none
        **************************************************************************/
        void addChild(SceneNode* _child);

        /**************************************************************************
        * Name:  removeChild(SceneNode* _child)
        * Description: Method used to remove a child SceneNode from the LinkedList
        *						'm_children'.
        * Inputs:
        *			- _child : SceneNode*, SceneNode to be removed from 'm_children'.
        * Returns: none
        **************************************************************************/
        void removeChild(SceneNode* _child);
};

#endif // __SCENENODE_H__
