#include "AtmosphericParticleSystem.h" // Implemented Class.


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  ParticleSystem()
* Description: Default constructor. Sets by default the particleSize to 1.0f
*						and calls ParticleSystem parametered constructor.
* Inputs: none
**************************************************************************/
AtmosphericParticleSystem::AtmosphericParticleSystem() : ParticleSystem(1.0f)
{
}


/**************************************************************************
* Name:  ~AtmosphericParticleSystem()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
AtmosphericParticleSystem::~AtmosphericParticleSystem()
{
}

/////////////////////////////// PROTECTED ///////////////////////////////////

/**************************************************************************
* Name: initializeParticle(Particle& _particle)
* Description: Method used to initialize a Particle.
* Inputs:
*			- _particle : Particle to initialize and set all of its attributes.
* Returns: none
**************************************************************************/
void AtmosphericParticleSystem::initializeParticle(Particle& _particle)
{
    /* Sets the spawn time of the particle to the current global time. */
    _particle.spawnTime = m_globalTime;

    /* Sets a random TTL : 3000 < TTL < 11500 .*/
    _particle.ttl = (Helpers::prand() * 3000.0f) + 8500.0f;

    /* Creates the circular caracteristics of the Particle. */
    float32 r = Helpers::prand() * 100.0f;
    float32 angle1 = Helpers::prand() * 2 * M_PI - M_PI;
    float32 angle2 = Helpers::prand() * 2 * M_PI - M_PI;

    /* Sets the position of the Particle according to the radius
        * and the two angles calculated previously
        */
    _particle.x = cosf(angle1)*sinf(angle2)*r;
    _particle.y = sinf(angle1)*sinf(angle2)*r + 2.0f;
    _particle.z = cosf(angle2) * r;

    /* Sets the direction of the Particle to a null vector. */
    _particle.dy = 0;
    _particle.dx = 0;
    _particle.dz = 0;

    /* Sets acceleration to a null vector. */
    _particle.ax = 0;
    _particle.ay = 0;
    _particle.az = 0;

    /* Sets the color of the particle to brown. */
    _particle.r = 0.803f;
    _particle.g = 0.522f;
    _particle.b = 0.257f;
}
