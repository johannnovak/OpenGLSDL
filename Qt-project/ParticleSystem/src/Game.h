#ifndef GAME_H
#define GAME_H

#include "GlWindow.h"
#include "Types.h"
#include "Scene.h"
#include "Shader.h"
#include "GraphicEngine.h"
#include "Camera.h"
#include "SceneNode.h"

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
        void render();

        void keyPressEvent(QKeyEvent *);

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
        FireParticle m_fireParticle;
};
#endif
