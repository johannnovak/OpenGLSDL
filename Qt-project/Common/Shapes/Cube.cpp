#include "cube.h"
#include <iostream>
#include <QDebug>

using namespace std;

Cube::Cube(float _width, float _height, float _depth, float _x, float _y, float _z, float _colorUp, float _colorDown, float _colorRight, float _colorLeft,float _colorFront, float _colorBack)
{
    m_depth = _depth;
    m_height = _height;
    m_width = _width;
    m_x = _x;
    m_y = _y;
    m_z = _z;

    m_colorUp = _colorUp;
    m_colorDown = _colorDown;
    m_colorRight = _colorRight;
    m_colorLeft = _colorLeft;
    m_colorFront = _colorFront;
    m_colorBack= _colorBack;
}

void Cube::drawShape(){

    float positions[] = {
        m_x - m_width/2, m_y - m_height/2, m_z + m_depth/2, // Front Face
        m_x - m_width/2, m_y + m_height/2, m_z + m_depth/2,
        m_x + m_width/2, m_y - m_height/2, m_z + m_depth/2,
        m_x + m_width/2, m_y + m_height/2, m_z + m_depth/2,

        m_x + m_width/2, m_y - m_height/2, m_z + m_depth/2, // Right Face
        m_x + m_width/2, m_y + m_height/2, m_z + m_depth/2,
        m_x + m_width/2, m_y - m_height/2, m_z - m_depth/2,
        m_x + m_width/2, m_y + m_height/2, m_z - m_depth/2,

        m_x + m_width/2, m_y - m_height/2, m_z - m_depth/2, // Back Face
        m_x + m_width/2, m_y + m_height/2, m_z - m_depth/2,
        m_x - m_width/2, m_y - m_height/2, m_z - m_depth/2,
        m_x - m_width/2, m_y + m_height/2, m_z - m_depth/2,

        m_x - m_width/2, m_y - m_height/2, m_z - m_depth/2, // Left Face
        m_x - m_width/2, m_y + m_height/2, m_z - m_depth/2,
        m_x - m_width/2, m_y - m_height/2, m_z + m_depth/2,
        m_x - m_width/2, m_y + m_height/2, m_z + m_depth/2,

        m_x - m_width/2, m_y + m_height/2, m_z + m_depth/2, // Up Face
        m_x - m_width/2, m_y + m_height/2, m_z - m_depth/2,
        m_x + m_width/2, m_y + m_height/2, m_z + m_depth/2,
        m_x + m_width/2, m_y + m_height/2, m_z - m_depth/2,

        m_x - m_width/2, m_y - m_height/2, m_z - m_depth/2, // Down Face
        m_x - m_width/2, m_y - m_height/2, m_z + m_depth/2,
        m_x + m_width/2, m_y - m_height/2, m_z - m_depth/2,
        m_x + m_width/2, m_y - m_height/2, m_z + m_depth/2
    };

    float colors[] = {
        m_colorFront,0,0,
        m_colorFront,0,0,
        m_colorFront,0,0,
        m_colorFront,0,0,

        0,m_colorRight,m_colorRight,
        0,m_colorRight,m_colorRight,
        0,m_colorRight,m_colorRight,
        0,m_colorRight,m_colorRight,

        m_colorBack,m_colorBack,0,
        m_colorBack,m_colorBack,0,
        m_colorBack,m_colorBack,0,
        m_colorBack,m_colorBack,0,

        0,0,m_colorLeft,
        0,0,m_colorLeft,
        0,0,m_colorLeft,
        0,0,m_colorLeft,

        m_colorUp,0,m_colorUp,
        m_colorUp,0,m_colorUp,
        m_colorUp,0,m_colorUp,
        m_colorUp,0,m_colorUp,

        m_colorDown,m_colorDown,m_colorDown,
        m_colorDown,m_colorDown,m_colorDown,
        m_colorDown,m_colorDown,m_colorDown,
        m_colorDown,m_colorDown,m_colorDown
    };

    // Récupère l'emplacement V-RAM de la variable "position"
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );

    // Enable
    glEnableVertexAttribArray( var1 );

    // Set la variable position
    // 1- variable position
    // 2 - size du vecteur
    // 3 - type des valeurs
    // 4 - normalisé ou pas => GL_TRUE/ GL_FALSE
    // 5 - pas dans le tableau, STRIDES
    // 6 - pointeur sur tableaux
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, positions );

    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, colors );

    // Draw arrays
    // 1 - Methode de draw
    // 2 - offset
    // 3 - Nombre de points ( 8 faces, 4 points par face)
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4*6 );

    // disable
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
