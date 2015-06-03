#include "Camera.h" // Impelement Class.

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  Camera(SceneNode& _node)
* Description: Default constructor. Assigns default values.
* Inputs:
*			- _node 	 SceneNode the Camera will be attached to.
**************************************************************************/
Camera::Camera(SceneNode& _node) 
   : m_projection(1), m_view(1), m_fov(45), m_aspect(640.0f / 480.0f), m_near(0.1f), m_far(1000.0f), m_node(_node)
{
}

/**************************************************************************
* Name:  ~Camera()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
Camera::~Camera()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: setFOV(float32 _fov)
* Description: Setter for the 'm_fov' attribute.
* Inputs:
*			- _fov : float32, angle representing the field of view.
* Returns: none
**************************************************************************/
void Camera::setFOV(float32 _fov)
{
    m_fov = _fov;
}

/**************************************************************************
* Name: getView()
* Description: Getter for the 'm_view' attribute. Computes it beforehand
*					with the formula : V = ((M)^(-1))^T.
* Inputs: none
* Returns:
*			- m_view : glm::mat4, 'm_view' attribute.
**************************************************************************/
glm::mat4& Camera::getView()
{
    m_view = glm::transpose(glm::inverse(m_node.computeWorldMatrix()));
    return m_view;
}

/**************************************************************************
* Name: getProjection()
* Description: Getter for the 'm_projection' attribute. Computes it from the
*					different from the attributes 'm_fov', 'm_aspect', 'm-near'
*					'm_near' and 'm_far' (done in the 'computeMatrices' method).
* Inputs: none
* Returns:
*			- m_projection: glm::mat4, 'm_projection' attribute.
**************************************************************************/
glm::mat4& Camera::getProjection()
{
    computeMatrices();
    return m_projection;
}

/**************************************************************************
* Name: getSceneNode()
* Description: Getter for the 'm_node' attribute.
* Inputs: none
**************************************************************************/
SceneNode& Camera::getSceneNode()
{
    return m_node;
}

/////////////////////////////// PRIVATE ///////////////////////////////////

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: computeMatrices()
* Description: Method used to compute the 'm_projection' matrix attribute
*						in function of the other attributes 'm_fov', 'm_aspect',
*						'm_near' and 'm_far' thanks to glm::perspective method.
* Inputs: none
* Returns: none
**************************************************************************/
void Camera::computeMatrices()
{
    m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}
