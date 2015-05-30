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
#include "FireParticle.h"

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
        long m_globalTime;
        unsigned int m_targetFps;
        bool m_quit;

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
        FireParticle m_fireParticle;
};
#endif
