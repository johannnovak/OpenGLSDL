#ifndef __SCENE_H__
#define __SCENE_H__

#include <SceneNode.h>


/**************************************************************************
* Class: Scene
* Description: Class designed to store all Objects the world is composed.
*						It acts as a Tree and is only composed of a root SceneNode.
*
**************************************************************************/
class Scene
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
        /* root Node containing child Nodes that
         *contains objects to render.
         */
        SceneNode* m_rootNode;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  Scene()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        Scene();

        /**************************************************************************
        * Name:  ~Scene()
        * Description: Default Destructor.
        * Inputs: none
        **************************************************************************/
        ~Scene();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: getRootNode()
        * Description: Getter for the 'm_rootNode' attribute.
        * Inputs: none
        * Returns:
        *			- m_rootNode : SceneNode*, pointer on the root SceneNode of the Scene.
        **************************************************************************/
        SceneNode* getRootNode();
};

#endif // __SCENE_H__
