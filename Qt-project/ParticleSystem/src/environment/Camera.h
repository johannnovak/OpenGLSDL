#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SceneNode.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


/**************************************************************************
* Class: Camera
* Description: Class designed to represent the Camera of the simulation.
*
**************************************************************************/
class Camera
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* 4*4 Projection matrix. */
        glm::mat4 m_projection;

        /* 4*4 View Matrix. */
        glm::mat4 m_view;

        /* Field of view of the camera. */
        float32 m_fov;

        /* Aspect ratio of the window. */
        float32 m_aspect;

        /* Distance to the near plane. */
        float32 m_near;

        /* Distance to the far plane. */
        float32 m_far;

        /* SceneNode where the camera is positionned. */
        SceneNode& m_node;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  Camera(SceneNode& _node)
        * Description: Default constructor.
        * Inputs:
        *			- _node 	 SceneNode the Camera will be attached to.
        **************************************************************************/
        Camera(SceneNode& _node);

        /**************************************************************************
        * Name:  ~Camera()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~Camera();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: setFOV(float32 _fov)
        * Description: Setter for the 'm_fov' attribute.
        * Inputs:
        *			- _fov : float32, angle representing the field of view.
        * Returns: none
        **************************************************************************/
        void setFOV(float32 _fov);

        /**************************************************************************
        * Name: getView()
        * Description: Getter for the 'm_view' attribute. Computes it beforehand
        *					with the formula : V = ((M)^(-1))^T.
        * Inputs: none
        * Returns:
        *			- m_view : glm::mat4, 'm_view' attribute.
        **************************************************************************/
        glm::mat4& getView();

        /**************************************************************************
        * Name: getProjection()
        * Description: Getter for the 'm_projection' attribute. Computes it from the
        *					different from the attributes 'm_fov', 'm_aspect', 'm-near'
        *					'm_near' and 'm_far' (done in the 'computeMatrices' method).
        * Inputs: none
        * Returns:
        *			- m_projection: glm::mat4, 'm_projection' attribute.
        **************************************************************************/
        glm::mat4& getProjection();

        /**************************************************************************
        * Name: getSceneNode()
        * Description: Getter for the 'm_node' attribute.
        * Inputs: none
        * Returns:
        *			- m_node: SceneNode&, 'm_node' attribute.
        **************************************************************************/
        SceneNode& getSceneNode();

/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: computeMatrices()
        * Description: Method used to compute the 'm_projection' matrix attribute
        *						in function of the other attributes 'm_fov', 'm_aspect',
        *						'm_near' and 'm_far' thanks to glm::perspective method.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        void computeMatrices();

};

#endif // __CAMERA_H__
