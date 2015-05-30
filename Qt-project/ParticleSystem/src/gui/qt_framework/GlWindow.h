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
        void timerEvent(QTimerEvent *);

		/*!
		*\brief Fonction d'initialization des structures des objets.
		*/
		virtual bool initializeObjects() = 0;

        virtual void renderGame(float _dt) = 0;

        /*!
		*\brief Appelé chaque fois que la fenêtre est redimensionnée.
		*/
		void resizeGL(int w, int h);


        float m_dt;

    protected:

        virtual void updateGame(float _dt) = 0;
        void paintGL(float _dt);
};


#define INTERFACE_GLWINDOW \
	bool initializeObjects(); \
	void render(); \

#endif
