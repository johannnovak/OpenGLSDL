#include "Pyramide.h"
#include <iostream>

Pyramide::Pyramide(float n, float rayon, float height)
{
    nbSides = n;
    this->rayon = rayon;
    this->height = height;
}


void Pyramide::drawShape()
{
    if(nbSides > 2)
    {
        float sideNb = 0;
        int size1 = 3*(nbSides+2);
        float positionsTop[size1];
        float colorsTop[size1];

        for(int i(0); i < size1; i = i+3)
        {
            if(i == 0){
                positionsTop[0] = 0;
                positionsTop[1] = 0;
                positionsTop[2] = height;

                colorsTop[0] = 1;
                colorsTop[1] = 1;
                colorsTop[2] = 1;

            }else{
                positionsTop[i]   = rayon * cos(sideNb*2*M_PI/nbSides);
                positionsTop[i+1] = rayon * sin(sideNb*2*M_PI/nbSides);
                positionsTop[i+2] = 0;

                colorsTop[i+0] = 0;
                colorsTop[i+1] = 0;
                colorsTop[i+2] = 0.5;

                ++sideNb;
            }
        }

        for(int i(0); i < size1; i = i+3){
            std::cout << "(" << positionsTop[i] << " " << positionsTop[i+1] << " " << positionsTop[i+2] << ")" << std::endl;

        }

        glFrontFace(GL_CW);

        GLint shaderPositionID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
        GLint shaderColorID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

        glEnableVertexAttribArray(shaderPositionID);
        glEnableVertexAttribArray(shaderColorID);

        glVertexAttribPointer(shaderPositionID, 3, GL_FLOAT, GL_FALSE, 0, positionsTop);
        glVertexAttribPointer(shaderColorID, 3, GL_FLOAT, GL_FALSE, 0, colorsTop);

        glDrawArrays(GL_TRIANGLE_FAN, 0, nbSides+2);
        glDrawArrays(GL_TRIANGLE_FAN, 1, nbSides+1);

        glDisableVertexAttribArray(shaderPositionID);
        glDisableVertexAttribArray(shaderColorID);
    }
}
