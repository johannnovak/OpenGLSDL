#include "FireParticleSystem.h" // Implemented Class.


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  FireParticleSystem()
* Description: Default constructor.
* Inputs: none
**************************************************************************/
FireParticleSystem::FireParticleSystem()
{
}


/**************************************************************************
* Name:  ~FireParticleSystem()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
FireParticleSystem::~FireParticleSystem()
{
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: initialize()
* Description: Method used to initialize the particle system.
* Inputs: none
* Returns: none
**************************************************************************/
void FireParticleSystem::initialize()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Initializing ParticleSystem...");

    srand(time(NULL));

    /* Gets the shader. */
    m_shader = ShaderBank::getShader("Shaders/Particle/fire");

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Registering variables...");

    /* Registers the uniform variables W, V, P matrixes along with the time t.*/
    m_shader->registerUniform("W");
    m_shader->registerUniform("V");
    m_shader->registerUniform("P");
    m_shader->registerUniform("t");

    /* Registers the in attributes for tjhe particle. */
    m_shader->registerAttribute("position");
    m_shader->registerAttribute("speed");
    m_shader->registerAttribute("acceleration");
    m_shader->registerAttribute("color");

    m_shader->registerAttribute("spawnTime");
    m_shader->registerAttribute("ttl");

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_DEBUG, "Creating "+ Helpers::uint32ToString(m_particleCount) +" particles...");

    /* Initializes all particles of the system. */
    m_particles = new Particle[m_particleCount];
    for (uint32 i = 0; i < m_particleCount; ++i)
        initializeParticle(m_particles[i]);

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "ParticleSystem initialized.");
}

/////////////////////////////// PROTECTED ///////////////////////////////////

/**************************************************************************
* Name: initializeParticle(Particle& _particle)
* Description: Method used to initialize a Particle.
* Inputs:
*			- _particle : Particle to initialize and set all of its attributes.
* Returns: none
**************************************************************************/
void FireParticleSystem::initializeParticle(Particle& _particle)
{
    /* Sets the spawn time of the particle to the current global time. */
    _particle.spawnTime = m_globalTime;

    /* Sets a random TTL : 500 < TTL < 1500 .*/
    _particle.ttl = Helpers::prand() * 1000.0f + 500.0f;

    /* Sets the position of the particle. */
    _particle.x = 0;
    _particle.y = 0;
    _particle.z = 0;

    /* Sets the direction of the particle on x and z with a
      * proportionality relation with the speed (and :
      * -0.0005 < speed < 0.0005, 0 < t < 1),
      * dx = t*v   and   dy = (1-t)*v
      */
    float32 speed = Helpers::prand() * 0.002f - 0.001f;
    float32 perc = Helpers::prand();
    _particle.dx = speed * perc;
    _particle.dy = 0;
    _particle.dz = speed * (1-perc);

    /* Sets acceleration on the y coordinate. */
    _particle.ax = 0;
    _particle.ay = 0.000005f;
    _particle.az = 0;

    /* Sets the color to red. */
    _particle.r = 1.0f;
    _particle.g = 0.0f;
    _particle.b = 0.0f;
}
