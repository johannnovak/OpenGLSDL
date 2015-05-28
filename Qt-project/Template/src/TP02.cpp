#include "TP02.h"

#include "Shapes/Basis.h"
#include "Shapes/humanoid/arm.h"
#include "Shapes/humanoid/head.h"
#include "Shapes/humanoid/leg.h"
#include "Shapes/humanoid/torso.h"

#include <iostream>
#include <vector>

using namespace std;

GLfloat angle1 = 0.0f;
GLfloat angle2 = 90.0f;

const GLfloat g_AngleSpeed = 10.0f;

vector<Object3D*> g_Objects;

Head* m_head = new Head();
Leg* m_leg1 = new Leg();
Leg* m_leg2 = new Leg();
Arm* m_arm1 = new Arm();
Arm* m_arm2 = new Arm();
Torso* m_torso = new Torso();

float anglejambe = 0;

bool leftLeg = true;

TP02::TP02()
{
    setWindowTitle(trUtf8("IN55-TP02"));
}


TP02::~TP02()
{
    for(int i(0); i < g_Objects.size(); ++i)
    {
        Object3D* o = g_Objects.at(i);
        delete(o);
    }
    g_Objects.clear();
}


bool
TP02::initializeObjects()
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
TP02::render()
{
	// Rendu des objets
    pushMatrix();
        // Initialisation de la caméra
        lookAt( 30  , 0  , 10  ,
            0  , 0  , 0  ,
            0  , 1  , 0  );
    popMatrix();

    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );

        // Draw du torse
        m_torso->draw();

        // Draw de la tête
        pushMatrix();
            translate(0,0,-(2.5f+1));
            m_head->draw();
        popMatrix();

        // draw des deux bras
        pushMatrix();
            translate(0,-(1.5f+0.5f),0);
            rotate(anglejambe,0,1,0);
            m_arm1->draw();
        popMatrix();
        pushMatrix();
            translate(0,(1.5f+0.5f),0);
            rotate(-anglejambe,0,1,0);
            m_arm2->draw();
        popMatrix();

        // draw des jambes
        pushMatrix();
            translate(0,-1.0f,(4.5f));
            rotate(anglejambe,0,1,0);
            m_leg1->draw();
        popMatrix();
        pushMatrix();
            translate(0,1.0f,(4.5f));
            rotate(-anglejambe,0,1,0);
            m_leg2->draw();
        popMatrix();
	popMatrix();

}

void
TP02::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
			break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;

        case Qt::Key_0:
            if(anglejambe + g_AngleSpeed > 15)
                leftLeg = false;
            else if(anglejambe - g_AngleSpeed < -15)
                leftLeg = true;
            if(leftLeg)
                anglejambe += g_AngleSpeed;
            else
                anglejambe -= g_AngleSpeed;
            break;
	}
}
