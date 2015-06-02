#ifndef GAME_H
#define GAME_H

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

class Game : public GlWindow
{
    public:
        Game();
        ~Game();

    protected:
        /*!
        *\brief Initialization des objets.
        */
        bool initializeObjects();

        /*!
        *\brief Rendu de la scène.
        */
        void renderGame(float _dt);

        void updateGame(float _dt) ;
    private:
        Scene m_scene;
        Shader m_shader;
        GraphicEngine m_graphics;

        Camera* m_mainCamera;

        SceneNode* m_importedObjectNode;
        Object3D* m_importedObject;

        SceneNode* m_cubeNode;
        Cube* m_cube;

        ParticleSystem m_particleSystem;
        AtmosphericParticleSystem m_atmosphericParticle;
        FireParticleSystem m_fireParticle;

};
#endif
