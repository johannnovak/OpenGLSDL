#ifndef __ABSTRACTPARTICLESYSTEM_H__
#define __ABSTRACTPARTICLESYSTEM_H__

#include "Shader.h"


/**************************************************************************
* Struct: Particle
* Description: Structure representing the composants of a particle. Used as
*						such and not a class because a Structure can be given to
*						OpenGL Shaders thanks to the GL_STRIDES composant.
**************************************************************************/
struct Particle
{
    /* Local position components. */
    float32 x, y, z;				// position in structure : 0

    /* Speed vector components. */
    float32 dx, dy, dz;			// position in structure : 3*sizeof(float32) + 0

    /* Acceleration vector components. */
    float32 ax, ay, az;   		// position in structure : 3*sizeof(float32 + 3*sizeof(float32) + 0

    /* Color components. */
    float32 r, g, b;				// position in structure : 3*sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 0

    /* Time To Live until disappearing. */
    float32 ttl;					// position in structure : 3*sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 0

    /* Time when the particle has been created. */
    float32 spawnTime;			// position in structure : sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 3*sizeof(float32) + 0
};


/**************************************************************************
* Class: AbstractParticleSystem
* Description: Abstract class designed to emit particles from a point in
*					the game space.
*
**************************************************************************/
class AbstractParticleSystem
{
/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:
        /* Float pointer on the first value of the view Matrix. */
        GLfloat* m_view;

        /* Float pointer on the first value of the projection Matrix. */
        GLfloat* m_projection;

        /* Float pointer on the first value of the world Matrix. */
        GLfloat* m_world;

        /* Number of particle the system has to emit. */
        uint32 m_particleCount;

        /* Pointer on the particles which have been emitted. */
        Particle* m_particles;

        /* Pointer on the shader where are registered all informations on the particles
         * and that is used to daw them.
         */
        Shader* m_shader;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  AbstractParticleSystem()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        AbstractParticleSystem();

        /**************************************************************************
        * Name:  AbstractParticleSystem(_particleCount)
        * Description: Constructor setting the 'm_particleCount' attribute.
        * Inputs:
        *			- _particleCount : Set the number of particle to emit by setting the
        *										'm_particleCount' attribute.
        **************************************************************************/
        AbstractParticleSystem(uint32 _particleCount);

        /**************************************************************************
        * Name:  ~AbstractParticleSystem()
        * Description: Default Destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~AbstractParticleSystem();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: setView(GLfloat* _view)
        * Description: Setter for the 'm_view' attribute.
        * Inputs:
        *			- _view : Pointer reference on the View matrix to assign to 'm_view'.
        * Returns: none
        **************************************************************************/
        void setView(GLfloat* _view);

        /**************************************************************************
        * Name: setProjection(GLfloat* _projection)
        * Description: Setter for the 'm_projection' attribute.
        * Inputs:
        *			- _projection : Pointer reference on the Projection matrix to
        *									assign to 'm_projection'.
        * Returns: none
        **************************************************************************/
        void setProjection(GLfloat* _projection);

        /**************************************************************************
        * Name: setWorld(GLfloat* _world)
        * Description: Setter for the 'm_world' attribute.
        * Inputs:
        *			- _world : Pointer reference on the World matrix to assign to
        *							'm_world'.
        * Returns: none
        **************************************************************************/
        void setWorld(GLfloat* _world);

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
        void setMatrices(GLfloat* _world, GLfloat* _view, GLfloat* _projection);

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: initialize()
        * Description: Abstract method used to initialize the particle system.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        virtual void initialize() = 0;

        /**************************************************************************
        * Name: update()
        * Description: Abstract method used to update the particle system and so update
        *					all particles' state (direction, speed, acceleration, etc...).
        * Inputs:
        *			-_dt : float, time difference when the last update occured.
        * Returns: none
        **************************************************************************/
        virtual void update(float _dt) = 0;

        /**************************************************************************
        * Name: draw()
        * Description: Abstract method used to draw the particle system.
        * Inputs:
        *			-_dt : float, time difference when the last rendering occured.
        * Returns: none
        **************************************************************************/
        virtual void draw(float _dt) = 0;

  /////////////////////////////// PROTECTED ///////////////////////////////////
    protected:

        /**************************************************************************
        * Name: initializeParticle(Particle& _particle)
        * Description: Abstract method used to initialize a Particle.
        * Inputs:
        *			- _particle : Reference on Particle to initialize and to set all of
        *								its attributes.
        * Returns: none
        **************************************************************************/
        virtual void initializeParticle(Particle& _particle) = 0;

        /**************************************************************************
        * Name: preDraw()
        * Description: Abstract method used to perform some pre-computations before
        *					calling the 'draw' method.
        * Inputs:
        *			-_dt : float, time difference when the last rendering occured.
        * Returns: none
        **************************************************************************/
        virtual void preDraw(float _dt) = 0;
};

#endif //  __ABSTRACTPARTICLESYSTEM_H__
