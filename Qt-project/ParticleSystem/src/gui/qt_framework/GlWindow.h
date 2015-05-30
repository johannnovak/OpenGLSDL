#ifndef GlWindow_h
#define GlWindow_h


#include "GlFramework.h"

#include <chrono>
#include <thread>
#include <QGLWidget>
#include <QKeyEvent>


class GlWindow : public QGLWidget, public GlFramework
{
	public: // methods
		GlWindow();
        virtual ~GlWindow();

        /*!
        *\brief Fonction d'initialization d'OpenGL, appelée à la création du
        *contexte de rendu.
        */
        virtual void initializeGL();

    private: // methods
		/*!
		*\brief Fonction d'initialization des structures des objets.
		*/
		virtual bool initializeObjects() = 0;

        virtual void render(float _dt) = 0;

        /*!
		*\brief Appelé chaque fois que la fenêtre est redimensionnée.
		*/
		void resizeGL(int w, int h);



    protected:
        long m_globalTime;
        unsigned int m_targetFps;
        bool m_quit;

        void updateGame(float _dt);
        void paintGL(float _dt);
};


#define INTERFACE_GLWINDOW \
	bool initializeObjects(); \
	void render(); \
	void keyPressEvent( QKeyEvent* event ); \


#endif
