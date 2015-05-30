#include "GlWindow.h"

GlWindow::GlWindow():m_dt(16)
{
    resize(1024, 768);
    startTimer(m_dt);
}

GlWindow::~GlWindow()
{
}

void GlWindow::initializeGL()
{
    init();
    initializeObjects();
}

void GlWindow::timerEvent(QTimerEvent * _event)
{
    paintGL(m_dt);
}

void GlWindow::paintGL(float _dt)
{
    updateGame(_dt);

    /* Draws the scene and its child. */
    renderGame(_dt);

    /* Updates QT window. */
    update();
}


void GlWindow::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );

    float a = w / static_cast<GLfloat>(h);
//	printf( "Size: (%d,%d) - AspectRatio: %f\n", w, h, a );

    setPerspective( 45.0f, a, 0.1f, 100.0f );
}
