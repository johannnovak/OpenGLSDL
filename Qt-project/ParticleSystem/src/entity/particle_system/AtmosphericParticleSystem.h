#ifndef __ATMOSPHERICPARTICLESYSTEM_H__
#define __ATMOSPHERICPARTICLESYSTEM_H__

#include "ParticleSystem.h"

/**************************************************************************
* Class: AtmosphericParticleSystem : public ParticleSystem
* Description: Class designed to emit atmospheric particles from a point in
*					the world. Particles emitted by such particle systems follow
*					a circular trajectory around an axis (like a sandstorm for
*					example).
*
**************************************************************************/
class AtmosphericParticleSystem : public ParticleSystem
{
    /////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

      /**************************************************************************
      * Name:  AtmosphericParticleSystem()
      * Description: Default constructor.
      * Inputs: none
      **************************************************************************/
      AtmosphericParticleSystem();

      /**************************************************************************
      * Name:  ~AtmosphericParticleSystem()
      * Description: Default Destructor.
      * Inputs: none
      **************************************************************************/
      virtual ~AtmosphericParticleSystem();

/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:

      /**************************************************************************
      * Name: initializeParticle(Particle& _particle)
      * Description: Method used to initialize a Particle.
      * Inputs:
      *			- _particle : Particle to initialize and set all of its attributes.
      * Returns: none
      **************************************************************************/
      virtual void initializeParticle(Particle& _particle);
};

#endif // __ATMOSPHERICPARTICLESYSTEM_H__
