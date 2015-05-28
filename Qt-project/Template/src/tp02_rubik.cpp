#include "tp02_rubik.h"

#include "Shapes/Basis.h"
#include "Shapes/cube.h"
#include "Shapes/Axis.h"
#include "Shapes/rubbik.h"

#include <iostream>
#include <vector>

using namespace std;

const GLfloat g_AngleSpeed = 10.0f;


TP02_Rubbik::TP02_Rubbik()
{
    setWindowTitle(trUtf8("IN55-TP02_Rubbik_Grue"));

    m_camangle1 = 0.0f;
    m_camangle2 = 270.0f;

    m_axis = new Axis();
    m_rubbik = new Rubbik(2);
    m_cube1 = new Cube(5,5,5,0,0,10,0.5,0.5,0.5,0.5,0.5,0.5);
    m_cube2 = new Cube(5,5,5,10,10,0,0.5,0.5,0.5,0.5,0.5,0.5);
}


TP02_Rubbik::~TP02_Rubbik()
{

}


bool
TP02_Rubbik::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    //glEnable( GL_CULL_FACE );

    // Chargement des shaders
    createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    return true;
}


void
TP02_Rubbik::render()
{
    // Rendu des objets
    pushMatrix();
        // Initialisation de la caméra
        lookAt( 80  , 5  , 15 ,
            0  , 10  , 0  ,
            0  , 1  , 0  );
    popMatrix();

    pushMatrix();
        rotate( m_camangle1, 0, 1, 0 );
        rotate( m_camangle2, 1, 0, 0 );

        m_axis->draw();

        /*m_cube1->draw();
        m_cube2->draw();*/

        m_rubbik->draw();

    popMatrix();

}

void
TP02_Rubbik::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
            m_camangle1 -= g_AngleSpeed;
            break;

        case Qt::Key_Right:
            m_camangle1 += g_AngleSpeed;
            break;

        case Qt::Key_Up:
            m_camangle2 -= g_AngleSpeed;
            break;

        case Qt::Key_Down:
            m_camangle2 += g_AngleSpeed;
            break;

        case Qt::Key_R:
            m_camangle1 = m_camangle2 = 0.0f;
            break;

    case Qt::Key_1:
        m_rubbik->addAngle(0,-10);
        break;
    case Qt::Key_2:
        m_rubbik->addAngle(0,10);
        break;
    case Qt::Key_4:
        m_rubbik->addAngle(1,-10);
        break;
    case Qt::Key_7:
        m_rubbik->addAngle(1,10);
        break;
    case Qt::Key_8:
        m_rubbik->addAngle(2,10);
        break;
    case Qt::Key_9:
        m_rubbik->addAngle(2,10);
        break;
    case Qt::Key_3:
        m_rubbik->addAngle(3,-10);
        break;
    case Qt::Key_6:
        m_rubbik->addAngle(3,10);
        break;
    }
}
