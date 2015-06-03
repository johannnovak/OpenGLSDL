#ifndef __GAME_H__
#define __GAME_H__

#include "Shader.h"
#include "GlWindow.h"
#include "Types.h"
#include "Scene.h"
#include "GraphicEngine.h"
#include "Camera.h"
#include "SceneNode.h"
#include "Cube.h"
#include "ParticleSystem.h"
#include "AtmosphericParticleSystem.h"
#include "FireParticleSystem.h"

/**************************************************************************
* Class: Game
* Description: Class inheriting from GLWindow. It is where the scene is
*					created, the shaders registered. It updates the simulation
*					and make the GraphicsEngine render the Scene.
*
**************************************************************************/
class Game : public GlWindow
{
/////////////////////////////// PRIVATE ///////////////////////////////////
    private:
         /* Scene containing all objects of the world. */
         Scene m_scene;

         /* Object used to render a Scene. */
         GraphicEngine m_graphics;

         /* Shader to use when telling the GraphicsEngine to do the rendering. */
         Shader m_shader;

         /* Quaternion based Camera of the Scene. */
         Camera* m_mainCamera;

         /* TODO */
         SceneNode* m_importedObjectNode;
         Object3D* m_importedObject;

         SceneNode* m_cubeNode;
         Cube* m_cube;

         ParticleSystem m_particleSystem;
         AtmosphericParticleSystem m_atmosphericParticle;
         FireParticleSystem m_fireParticle;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

         /**************************************************************************
         * Name: Game()
         * Description: Default constructor.
         * Inputs: none
         **************************************************************************/
         Game();

         /**************************************************************************
         * Name: ~Game()
         * Description: Default destructor.
         * Inputs: none
         **************************************************************************/
         ~Game();

/////////////////////////////// PROTECTED ///////////////////////////////////
    protected:
    //============================= OPERATIONS ==============================================

         /**************************************************************************
         * Name: initializeObjects()
         * Description: Method used to initialize all of the objects of the scene
         *						along with the shader attributes registering. All created
         *						are added to the scene inside SceneNodes.
         * Inputs: none
         * Returns:
         *			- True if no errors occurerd.
         *			- False otherwise.
         **************************************************************************/
         bool initializeObjects();

         /**************************************************************************
         * Name: updateGame(float32 _dt)
         * Description: Method used to update the different objects that composes
         *						the scene. This is where the inputs can be tested
         *						by the InputManager in order to move/delete objects,
         *						stop the program, change parameters, etc ...
         * Input:
         *			- _dt : float32, time interval since the last rendering.
         * Returns: none
         **************************************************************************/
         void updateGame(float32 _dt) ;

         /**************************************************************************
         * Name: renderGame(float32 _dt)
         * Description: Method used to do the rendering. It transmits shader variables
         *					, tells the graphicsEngine to draw the scene, but also
         *					draws other objects.
         * Inputs:
         *			- _dt : float32, time interval since the last rendering.
         * Returns: none
         **************************************************************************/
         void renderGame(float32 _dt);
};
#endif // __GAME_H__
