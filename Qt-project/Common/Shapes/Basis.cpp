//*****************************************************************************
//
// Class: Basis
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2014-04-02
//
//*****************************************************************************


#include "Shapes/Basis.h"


GLfloat g_TabColors[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};


Basis::Basis( GLfloat length )
{
    for( GLuint i = 0; i < 6*3; ++i )
    {
        m_TabVertices[i] = 0.0f;
    }

    m_TabVertices[3] = length;
    m_TabVertices[10] = length;
    m_TabVertices[17] = length;
}

void Basis::drawCube(float x, float y, float z, float s)
{
    float demiS = s/2;

    float positions[] = {
        x - demiS, y - demiS, z + demiS, // Front Face
        x - demiS, y + demiS, z + demiS,
        x + demiS, y - demiS, z + demiS,
        x + demiS, y + demiS, z + demiS,

        x + demiS, y - demiS, z + demiS, // Right Face
        x + demiS, y + demiS, z + demiS,
        x + demiS, y - demiS, z - demiS,
        x + demiS, y + demiS, z - demiS,

        x + demiS, y - demiS, z - demiS, // Back Face
        x + demiS, y + demiS, z - demiS,
        x - demiS, y - demiS, z - demiS,
        x - demiS, y + demiS, z - demiS,

        x - demiS, y - demiS, z - demiS, // Left Face
        x - demiS, y + demiS, z - demiS,
        x - demiS, y - demiS, z + demiS,
        x - demiS, y + demiS, z + demiS,

        x - demiS, y + demiS, z + demiS, // Up Face
        x - demiS, y + demiS, z - demiS,
        x + demiS, y + demiS, z + demiS,
        x + demiS, y + demiS, z - demiS,

        x - demiS, y - demiS, z - demiS, // Down Face
        x - demiS, y - demiS, z + demiS,
        x + demiS, y - demiS, z - demiS,
        x + demiS, y - demiS, z + demiS,
    };

   /* float positions[] = {
        // Front face
        x - half, y + half, z - half,
        x - half, y - half, z - half,
        x + half, y - half, z - half,
        x + half, y + half, z - half,

        // Right face
        x + half, y + half, z - half,
        x + half, y + half, z + half,
        x + half, y - half, z + half,
        x + half, y - half, z - half,

        // Back face
        x + half, y + half, z + half,
        x - half, y + half, z + half,
        x - half, y - half, z + half,
        x + half, y - half, z + half,

        // Left face
        x - half, y + half, z + half,
        x - half, y + half, z - half,
        x - half, y - half, z - half,
        x - half, y - half, z + half,

        // Up face
        x - half, y + half, z - half,
        x + half, y + half, z - half,
        x + half, y + half, z + half,
        x - half, y + half, z + half,

        // Down face
        x - half, y - half, z - half,
        x + half, y - half, z - half,
        x + half, y - half, z + half,
        x - half, y - half, z + half
    };*/

    float colors[] = {
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,

        0, 1, 0,
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,

        0.5f, 0, 0.5f,
        0.5f, 0, 0.5f,
        0.5f, 0, 0.5f,
        0.5f, 0, 0.5f,

        0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,

        0, 0.5f, 0.5f,
        0, 0.5f, 0.5f,
        0, 0.5f, 0.5f,
        0, 0.5f, 0.5f,
    };

    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, positions );
    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, colors );
    glDrawArrays( GL_TRIANGLES, 0, 4*8 );
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );

}

void
Basis::drawShape()
{
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );
    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_TabColors );
    glDrawArrays( GL_LINES, 0, 6 );
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
