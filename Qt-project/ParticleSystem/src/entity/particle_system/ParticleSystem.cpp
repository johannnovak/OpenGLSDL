#include "ParticleSystem.h" // Implemented class.

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  ParticleSystem()
* Description: Default constructor. Sets by default the particleCount to 1000,
*						the globalTime to 0 and the particleSize to 5.0f.
* Inputs: none
**************************************************************************/
ParticleSystem::ParticleSystem() : AbstractParticleSystem(1000), m_globalTime(0), m_particleSize(5.0f)
{
}

/**************************************************************************
* Name:  ParticleSystem()
* Description: Parametered constructor. Sets by default the particleCount to 1000
*						and the globalTime to 0.
* Inputs:
*			- _particleSize : float32, size of the Particles to be emitted.
**************************************************************************/
ParticleSystem::ParticleSystem(float32 _particleSize) : AbstractParticleSystem(1000), m_globalTime(0), m_particleSize(_particleSize)
{
}

/**************************************************************************
* Name:  ~ParticleSystem()
* Description: Default Destructor.
* Inputs: none
**************************************************************************/
ParticleSystem::~ParticleSystem()
{
    delete[] m_particles;
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: initialize()
* Description: Method used to initialize the particle system.
* Inputs: none
* Returns: none
**************************************************************************/
void ParticleSystem::initialize()
{
    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "Initializing ParticleSystem...");

    /* Gets the shader */
    m_shader = ShaderBank::getShader("Shaders/Particle/fade_in_out");

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
    for (unsigned int i = 0; i < m_particleCount; ++i)
        initializeParticle(m_particles[i]);

    LogManager::pushEvent(LogEventType::LogEventType_ALL_LOG_EVENT, LogLevel::LogLevel_INFO, "ParticleSystem initialized.");
}

/**************************************************************************
* Name: update()
* Description: Method used to update the particle system and so resets
*						all dead particles.
* Inputs:
*			-_dt : float, time difference when the last update occured.
* Returns: none
**************************************************************************/
void ParticleSystem::update(float _dt)
{
    /* Adds update time to the global time. */
    m_globalTime += _dt;

    /* For all Particles, if they are dead, they are re-initialized. */
    for (unsigned int i = 0; i < m_particleCount; ++i)
        if (m_particles[i].ttl + m_particles[i].spawnTime <= m_globalTime)
            initializeParticle(m_particles[i]);
}

/**************************************************************************
* Name: draw()
* Description: Method used to draw the particle system. It first activate the
*						transmits the shader, then it transmits the different
*						uniform variables, gets the different attributes and
*						draws all the particles thanks to the STRIDE of the
*						'Particle' structure defining the number of floats to skip
*						between the different Particles to draw.
* Inputs:
*			-_dt : float, time difference when the last rendering occured.
* Returns: none
**************************************************************************/
void ParticleSystem::draw(float _dt)
{
    /* Activates the shader and transmits the uniform variables. */
    m_shader->activate();
    m_shader->transmitUniformMat4("W", m_world, GL_FALSE);
    m_shader->transmitUniformMat4("V", m_view, GL_FALSE);
    m_shader->transmitUniformMat4("P", m_projection, GL_FALSE);

    m_shader->transmitUniformFloat("t", m_globalTime);

    /* Do pre-draw computing. */
    preDraw(_dt);

    /* Casts the Particle array into a GLfloat. */
    GLfloat* particles_to_float = (float*)m_particles;

    /* Send GLfloat arrays to Shader in order to give values to 'in' shader variables. */
    glVertexAttribPointer(m_shader->getAttrLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 0);
    glVertexAttribPointer(m_shader->getAttrLocation("speed"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 3);
    glVertexAttribPointer(m_shader->getAttrLocation("acceleration"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 6);
    glVertexAttribPointer(m_shader->getAttrLocation("color"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 9);

    glVertexAttribPointer(m_shader->getAttrLocation("ttl"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 12);
    glVertexAttribPointer(m_shader->getAttrLocation("spawnTime"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), particles_to_float + 13);

    /* Enables all attributes */
    m_shader->enableAllAttrib();

    /* Sets the point size to the ParticleSize. */
    glPointSize(m_particleSize);

    /* Calls the shader to draw the Particles. */
    glDrawArrays(GL_POINTS, 0, m_particleCount);

    /* Disables all shader attributes. */
    m_shader->disableAllAttrib();
}

/////////////////////////////// PROTECTED ///////////////////////////////////

/**************************************************************************
* Name: initializeParticle(Particle& _particle)
* Description: Method used to initialize a Particle.
* Inputs:
*			- _particle : Particle to initialize and set all of its attributes.
* Returns: none
**************************************************************************/
void ParticleSystem::initializeParticle(Particle& _particle)
{
    /* Sets the spawn time of the particle to the current global time. */
    _particle.spawnTime = m_globalTime;

    /* Sets a random TTL : 1500 < TTL < 2500 .*/
    _particle.ttl = (Helpers::prand() * 1000) + 1500;

    /* Sets the position of the particle. */
    _particle.x = Helpers::prand()*7.5f - 7.5f / 2.0f;
    _particle.y = 5.0f;
    _particle.z = Helpers::prand()*7.5f - 7.5f / 2.0f;

    /* Sets the direction of the particle (around y axis). */
    _particle.dy = -(0.005f * Helpers::prand());
    _particle.dx = 0; // 0.002f * prand() - 0.001f;
    _particle.dz = 0; // 0.002f * prand() - 0.001f;

    /* Sets no acceleration. */
    _particle.ax = 0;
    _particle.ay = 0;
    _particle.az = 0;

    /* Sets the color to blue. */
    _particle.r = 0;
    _particle.g = 0;
    _particle.b = 1;
}

/**************************************************************************
* Name: preDraw()
* Description: Method used to perform some pre-computations before
*					calling the 'draw' method.
* Inputs:
*			-_dt : float, time difference when the last rendering occured.
* Returns: none
**************************************************************************/
void ParticleSystem::preDraw(float)
{}
