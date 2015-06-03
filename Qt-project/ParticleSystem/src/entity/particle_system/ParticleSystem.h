#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "AbstractParticleSystem.h"
#include "ShaderBank.h"
#include "Helpers.h"

#include <ctime>
#include <random>


/**************************************************************************
* Class: ParticleSystem : public AbstractParticleSystem
* Description: Class designed to reprensent a standard ParticleSystem which
*						from its center emit particles around the y axis.
**************************************************************************/
class ParticleSystem : public AbstractParticleSystem
{

/////////////////////////////// PROTECTED ///////////////////////////////////
  protected:
      /* Time since the beginning of the simulation. */
      float32 m_globalTime;

      /* Size of the particles. */
      float32 m_particleSize;

/////////////////////////////// PUBLIC ///////////////////////////////////////
    public:

    //============================= LIFECYCLE =======================================

      /**************************************************************************
      * Name:  ParticleSystem()
      * Description: Default constructor.
      * Inputs: none
      **************************************************************************/
      ParticleSystem();

      /**************************************************************************
      * Name:  ParticleSystem(float32 _particleSize)
      * Description: Parametered constructor. Sets by default the particleCount to 1000
      *						and the globalTime to 0.
      * Inputs:
      *			- _particleSize : float32, size of the Particles to be emitted.
      **************************************************************************/
      ParticleSystem(float32 _particleSize);

      /**************************************************************************
      * Name:  ~ParticleSystem()
      * Description: Default Destructor.
      * Inputs: none
      **************************************************************************/
      ~ParticleSystem();

    //============================= OPERATIONS ==============================================

      /**************************************************************************
      * Name: initialize()
      * Description: Method used to initialize the particle system.
      * Inputs: none
      * Returns: none
      **************************************************************************/
      virtual void initialize();

      /**************************************************************************
      * Name: update(float32 _dt)
      * Description: Method used to update the particle system and so update
      *					all particles' state (direction, speed, acceleration, etc...).
      * Inputs:
      *			-_dt : float32, time difference when the last update occured.
      * Returns: none
      **************************************************************************/
      void update(float32 _dt);

      /**************************************************************************
      * Name: draw(float32 _dt)
      * Description: Method used to draw the particle system.
      * Inputs:
      *			-_dt : float, time difference when the last rendering occured.
      * Returns: none
      **************************************************************************/
      void draw(float32 _dt);


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

      /**************************************************************************
      * Name: preDraw(float32 _dt)
      * Description: Method used to perform some pre-computations before
      *					calling the 'draw' method.
      * Inputs:
      *			-_dt : float32, time difference when the last rendering occured.
      * Returns: none
      **************************************************************************/
      virtual void preDraw(float32 _dt);
};

#endif // __PARTICLESYSTEM_H__
