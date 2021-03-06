#include "Scene.h" // Implemented Class.

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  Scene()
* Description: Default constructor. Sets the 'm_rootNode' attribute to a new
*						SceneNode pointer.
* Inputs: none
**************************************************************************/
Scene::Scene() : m_rootNode(new SceneNode())
{
}

/**************************************************************************
* Name:  ~Scene()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
Scene::~Scene()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: getRootNode()
* Description: Getter for the 'm_rootNode' attribute.
* Inputs: none
* Returns:
*			- m_rootNode : SceneNode*, pointer on the root SceneNode of the Scene.
**************************************************************************/
SceneNode* Scene::getRootNode()
{
    return m_rootNode;
}

std::vector<ParticleSystem*> &Scene::getAllParticleSystems()
{
	
}
