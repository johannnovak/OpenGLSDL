#ifndef FIREPARTICLESYSTEM_H
#define FIREPARTICLESYSTEM_H

#include "ParticleSystem.h"


/**************************************************************************
* Class: FireParticleSystem : public ParticleSystem
* Description: Class designed to emit Fire particles from a point in
*					the world. Particles emitted by such particle systems follow
*					a circular trajectory around an axis (like a sandstorm for
*					example).
*
**************************************************************************/
class FireParticleSystem : 	public ParticleSystem
{
/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  FireParticleSystem()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        FireParticleSystem();

        /**************************************************************************
        * Name:  ~FireParticleSystem()
        * Description: Default Destructor.
        * Inputs: none
        **************************************************************************/
        virtual ~FireParticleSystem();

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: initialize()
        * Description: Method used to initialize the particle system.
        * Inputs: none
        * Returns: none
        **************************************************************************/
        virtual void initialize();

/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:

        /**************************************************************************
        * Name: initializeParticle(Particle& _particle)
        * Description: Method used to initialize a Particle.
        * Inputs:
        *			- _particle : Particle to initialize and set all of its attributes.
        * Returns: none
        **************************************************************************/
        void initializeParticle(Particle& _particle);
};

#endif // FIREPARTICLESYSTEM_H
