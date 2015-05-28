#include "Axis.h"

Axis::Axis()
{
}

void Axis::drawShape(){

    float positionsX[] = {
        0, 0, 0,
        150,0, 0
    };

    float colorX[] = {
        255, 0, 0,
        255, 0, 0
    };

    float positionsY[] = {
        0, 0, 0,
        0,150, 0
    };

    float colorY[] = {
        0, 255, 0,
        0, 255,0
    };

    float positionsZ[] = {
        0, 0, 0,
        0, 0, 150
    };

    float colorZ[] = {
        0, 0, 255,
        0, 0, 255
    };

    glFrontFace(GL_CW);

    // Récupère l'emplacement V-RAM de la variable "position"
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );

    // Enable
    glEnableVertexAttribArray( var1 );
    glEnableVertexAttribArray( var2 );

    // Set la variable position
    // 1- variable position
    // 2 - size du vecteur
    // 3 - type des valeurs
    // 4 - normalisé ou pas => GL_TRUE/ GL_FALSE
    // 5 - pas dans le tableau, STRIDES
    // 6 - pointeur sur tableaux
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, positionsX );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, colorX );

    // Draw arrays
    // 1 - Methode de draw
    // 2 - offset
    // 3 - Nombre de points ( 8 faces, 4 points par face)
    glDrawArrays( GL_LINES, 0, 2);


    // Set la variable position
    // 1- variable position
    // 2 - size du vecteur
    // 3 - type des valeurs
    // 4 - normalisé ou pas => GL_TRUE/ GL_FALSE
    // 5 - pas dans le tableau, STRIDES
    // 6 - pointeur sur tableaux
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, positionsY );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, colorY );

    // Draw arrays
    // 1 - Methode de draw
    // 2 - offset
    // 3 - Nombre de points ( 8 faces, 4 points par face)
    glDrawArrays( GL_LINES, 0, 2);


    // Set la variable position
    // 1- variable position
    // 2 - size du vecteur
    // 3 - type des valeurs
    // 4 - normalisé ou pas => GL_TRUE/ GL_FALSE
    // 5 - pas dans le tableau, STRIDES
    // 6 - pointeur sur tableaux
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, positionsZ );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, colorZ );

    // Draw arrays
    // 1 - Methode de draw
    // 2 - offset
    // 3 - Nombre de points ( 8 faces, 4 points par face)
    glDrawArrays( GL_LINES, 0, 2);

    // disable
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
