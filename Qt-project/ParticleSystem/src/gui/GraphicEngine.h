#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "Shader.h"
#include "Object3D.h"
#include "SceneNode.h"
#include "Scene.h"

#include "glm/glm.hpp"

/**************************************************************************
* Class: GraphicEngine
* Description: Class designed to handle the rendering of the scene via
*						OpenGL.
*
**************************************************************************/
class GraphicEngine
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* Pointer on the current shader used when rendering. */
         Shader* m_currentShader;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  GraphicEngine()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
         GraphicEngine();

         /**************************************************************************
         * Name:  ~GraphicEngine()
         * Description: Default destructor.
         * Inputs: none
         **************************************************************************/
         virtual ~GraphicEngine();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: setShader(Shader* _shader)
        * Description: Setter for the 'm_currentShader' attribute.
        * Inputs: none
        *			- _shader : Shader*, pointer on the current shader to use.
        * Returns: none
        **************************************************************************/
        void setShader(Shader* _shader);

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: drawObject3D(Object3D& _object)
        * Description: Draws an Object3D.
        * Inputs:
        *			- _object : Object3D&, reference on the Object3D to draw in the scene.
        * Returns: none
        **************************************************************************/
        void drawObject3D(Object3D& _object);

        /**************************************************************************
        * Name: drawSceneNode(SceneNode& _node)
        * Description: Draws a SceneNode and its associated Object3D (with drawObject3D).
        * Inputs:
        *			- _node : SceneNode&, Node of the Scene to draw.
        * Returns: none
        **************************************************************************/
        void drawSceneNode(SceneNode& _node);

        /**************************************************************************
        * Name: drawScene(Scene& _scene)
        * Description: Draws the entire Scene.
        * Inputs:
        *			- _scene : Scene&, Scene to draw.
        * Returns: none
        **************************************************************************/
        void drawScene(Scene& _scene);

/////////////////////////////// PRIVATE ///////////////////////////////////
    private:

        /**************************************************************************
        * Name: drawSceneNode(SceneNode& _node, const glm::mat4& world)
        * Description: Draws a SceneNode and its associated Object3D (with drawObject3D).
        *						It then calls drawSceneNode for all of its children (recursive).
        * Inputs:
        *			- _node  : SceneNode&, Node of the Scene to draw.
        *			- _world : const glm::mat4&, World Matrix, used to draw the children.
        * Returns: none
        **************************************************************************/
        void drawSceneNode(SceneNode& _node, const glm::mat4& _world);
};

#endif // GRAPHICENGINE_H
