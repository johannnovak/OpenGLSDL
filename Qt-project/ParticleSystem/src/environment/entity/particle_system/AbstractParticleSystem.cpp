#include "AbstractParticleSystem.h" // Implemented class.

/////////////////////////////// PUBLIC ///////////////////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  AbstractParticleSystem()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
AbstractParticleSystem::AbstractParticleSystem()
{
}

/**************************************************************************
* Name:  AbstractParticleSystem(_particleCount)
* Description: Constructor setting the 'm_particleCount' attribute.
* Inputs:
*			- _particleCount : Set the number of particle to emit by setting the
*										'm_particleCount' attribute.
**************************************************************************/
AbstractParticleSystem::AbstractParticleSystem(uint32 _particleCount) : m_particleCount(_particleCount)
{
}

/**************************************************************************
* Name:  ~AbstractParticleSystem()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
AbstractParticleSystem::~AbstractParticleSystem()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: setView(GLfloat* _view)
* Description: Setter for the 'm_view' attribute.
* Inputs:
*			- _view : Pointer reference on the View matrix to assign to 'm_view'.
* Returns: none
**************************************************************************/
void AbstractParticleSystem::setView(GLfloat* _view)
{
    m_view = _view;
}

/**************************************************************************
* Name: setProjection(GLfloat* _projection)
* Description: Setter for the 'm_projection' attribute.
* Inputs:
*			- _projection : Pointer reference on the Projection matrix to
*									assign to 'm_projection'.
* Returns: none
**************************************************************************/
void AbstractParticleSystem::setProjection(GLfloat* _projection)
{
    m_projection = _projection;
}

/**************************************************************************
* Name: setWorld(GLfloat* _world)
* Description: Setter for the 'm_world' attribute.
* Inputs:
*			- _world : Pointer reference on the World matrix to assign to
*							'm_world'.
* Returns: none
**************************************************************************/
void AbstractParticleSystem::setWorld(GLfloat* _world)
{
    m_world = _world;
}

/**************************************************************************
* Name: setMatrices(GLfloat* _view, GLfloat* _projection, GLfloat* _world)
* Description: Method used to set the attributes 'm_view', 'm_projection and
*					'm_world'.
* Inputs:
*			- _view 			: Pointer reference on the View matrix to assign to 'm_view'.
*			- _projection 	: Pointer reference on the Projection matrix to
*									assign to 'm_projection'.
*			- _world 		: Pointer reference on the World matrix to assign to
*									'm_world'.
* Returns: none
**************************************************************************/
void AbstractParticleSystem::setMatrices(GLfloat* _world, GLfloat* _view, GLfloat* _projection)
{
    setWorld(_world);
    setView(_view);
    setProjection(_projection);
}
