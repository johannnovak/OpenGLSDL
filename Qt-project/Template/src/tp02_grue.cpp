#include "tp02_grue.h"

#include "Shapes/Basis.h"
#include "Shapes/cube.h"
#include "Shapes/Axis.h"
#include "Shapes/Cylinder.h"

#include <iostream>
#include <vector>

using namespace std;

GLfloat glangle1 = 0.0f;
GLfloat glangle2 = 270.0f;

const GLfloat g_AngleSpeed = 10.0f;

Axis* axis = new Axis();

Cube* base = new Cube(8.0f, 2.0f, 1.0f,
                      0.0f, 0.0f, 0.0f,
                      0.6f,0.5f,0.4f,0.3f,0.2f,0.1f);
Cylinder* cylinder = new Cylinder(1.0f, 8.0f,
                                 0.0f,0.0f,0.0f,
                                 0.6f,0.1f);
Cube* top = new Cube(15.0f, 3.0f, 1.0f,
                     0.0f, 0.0f, 0.0f,
                     0.1f,0.1f,0.6f,0.8f,1.0f,0.7f);
Cylinder* claw = new Cylinder(0.2f, 5.0f,0.0f,0.0f,0.0f,
                              0.5f,1.0f);

Cube* weight = new Cube(3.0f, 3.0f, 3.0f,
                        0.0f, 0.0f, 0.0f,
                        1.0f, 0.4f, 0.6f, 0.4f, 0.2f, 0.7f);

TP02_Grue::TP02_Grue()
{
    setWindowTitle(trUtf8("IN55-TP02_Grue"));
}


TP02_Grue::~TP02_Grue()
{

}


bool
TP02_Grue::initializeObjects()
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
TP02_Grue::render()
{
    // Rendu des objets
    pushMatrix();
        // Initialisation de la caméra
        lookAt( 30  , 5  , 15 ,
            0  , 10  , 0  ,
            0  , 1  , 0  );
    popMatrix();

    pushMatrix();
        rotate( glangle1, 0, 1, 0 );
        rotate( glangle2, 1, 0, 0 );

        axis->draw();

        base->draw();

        pushMatrix();
            translate(0,0.0,0.5f);
            cylinder->draw();
            pushMatrix();
                translate(0.0f, 2.5f, 7.5f);
                top->draw();
                pushMatrix();
                    translate(7.5f,0.0f,-(5.0f+0.5f));
                    claw->draw();
                popMatrix();
                pushMatrix();
                    translate(-7.5f, 0.0f,-(1.5f+0.5f));
                    weight->draw();
                popMatrix();
            popMatrix();
        popMatrix();
    popMatrix();

}

void
TP02_Grue::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
            glangle1 -= g_AngleSpeed;
            break;

        case Qt::Key_Right:
            glangle1 += g_AngleSpeed;
            break;

        case Qt::Key_Up:
            glangle2 -= g_AngleSpeed;
            break;

        case Qt::Key_Down:
            glangle2 += g_AngleSpeed;
            break;

        case Qt::Key_R:
            glangle1 = glangle2 = 0.0f;
            break;
    }
}
