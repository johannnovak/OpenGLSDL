#include "Cylinder.h"

Cylinder::Cylinder(float _rayon, float _height, float _x, float _y, float _z, float _colorUp, float  _colorDown)
{
    this->rayon = _rayon;
    this->height = _height;

    m_x = _x;
    m_y = _y;
    m_z = _z;

    m_colorUp = _colorUp;
    m_colorDown = _colorDown;

}

void Cylinder::drawShape()
{
    int nbCirclePoint = 30;
    float sideNb = 0;
    int size = 3*(nbCirclePoint+1);


    float positionsTop[size];
    float colorsTop[size];

    float positionsBottom[size];
    float colorsBottom[size];

    float sidePosition[size*2];
    float sideColor[size*2];

    for(int i(0); i < size; i = i+3)
    {
            positionsTop[i]   = m_x + rayon * cos(sideNb*2*M_PI/nbCirclePoint);
            positionsTop[i+1] = m_y + rayon * sin(sideNb*2*M_PI/nbCirclePoint);
            positionsTop[i+2] = m_z + height;

            colorsTop[i+0] = 0;
            colorsTop[i+1] = 0;
            colorsTop[i+2] = m_colorUp;

            ++sideNb;
    }

    for(int i(0); i < size; i = i+3)
    {
            positionsBottom[i+0] = m_x + rayon * cos(sideNb*2*M_PI/nbCirclePoint);
            positionsBottom[i+1] = m_y + rayon * sin(sideNb*2*M_PI/nbCirclePoint);
            positionsBottom[i+2] = m_z;

            colorsBottom[i+0] = 0;
            colorsBottom[i+1] = m_colorDown;
            colorsBottom[i+2] = 0;

            ++sideNb;
    }

    int j =0;
    for(int i(0); i < size*2; i = i+6)
    {
        sidePosition[i+0] = positionsBottom[j+0];
        sidePosition[i+1] = positionsBottom[j+1];
        sidePosition[i+2] = positionsBottom[j+2];

        sidePosition[i+3] = positionsTop[j+0];
        sidePosition[i+4] = positionsTop[j+1];
        sidePosition[i+5] = positionsTop[j+2];

        sideColor[i+0] = colorsBottom[j+0];
        sideColor[i+1] = colorsBottom[j+1];
        sideColor[i+2] = colorsBottom[j+2];

        sideColor[i+3] = colorsTop[j+0];
        sideColor[i+4] = colorsTop[j+1];
        sideColor[i+5] = colorsTop[j+2];
        j = j + 3;
    }

    glFrontFace(GL_CW);

    GLint shaderPositionID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint shaderColorID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(shaderPositionID);
    glEnableVertexAttribArray(shaderColorID);

    glVertexAttribPointer(shaderPositionID, 3, GL_FLOAT, GL_FALSE, 0, positionsTop);
    glVertexAttribPointer(shaderColorID, 3, GL_FLOAT, GL_FALSE, 0, colorsTop);

    glDrawArrays(GL_TRIANGLE_FAN, 0, nbCirclePoint+1);

    glVertexAttribPointer(shaderPositionID, 3, GL_FLOAT, GL_FALSE, 0, positionsBottom);
    glVertexAttribPointer(shaderColorID, 3, GL_FLOAT, GL_FALSE, 0, colorsBottom);

    glDrawArrays(GL_TRIANGLE_FAN, 0, nbCirclePoint+1);

    glVertexAttribPointer(shaderPositionID, 3, GL_FLOAT, GL_FALSE, 0, sidePosition);
    glVertexAttribPointer(shaderColorID, 3, GL_FLOAT, GL_FALSE, 0, sideColor);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (nbCirclePoint+1)*2);

    glDisableVertexAttribArray(shaderPositionID);
    glDisableVertexAttribArray(shaderColorID);
}
