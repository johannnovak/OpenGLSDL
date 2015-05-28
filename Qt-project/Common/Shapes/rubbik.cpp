#include "rubbik.h"

Rubbik::Rubbik(int _nb)
{
    m_nb = _nb;
    angles = new int[m_nb*m_nb];
    for(int i(0); i < m_nb*m_nb; ++i)
        angles[i] = 0;
    xTurning = false;
    yTurning = false;
    zTurning = false;
}

void Rubbik::drawShape()
{
    float width = 5;
    float height = 5;
    float depth = 5;

    float interval = 9.0f;

    Cube**** cubeMatrix = new Cube***[m_nb];

    for(int i(0); i < m_nb; ++i)
    {
        cubeMatrix[i] = new Cube**[m_nb];
        for(int j(0); j < m_nb; ++j)
        {
            cubeMatrix[i][j] = new Cube*[m_nb];
            for(int k(0); k < m_nb; ++k)
                cubeMatrix[i][j][k] = new Cube(width,height,depth,
                                        0.0f + i*interval, 0.0f + j*interval, 0.0f+k*interval,
                                       0.1f, 0.9f, 0.4f, 0.6f, 0.7f, 0.9f);
        }
    }

    m_Framework->translate(
                           -(m_nb*width  + (m_nb-1)*interval)/4,
                           -(m_nb*height + (m_nb-1)*interval)/4,
                           -(m_nb*depth  + (m_nb-1)*interval)/4
                           );


    for(int i(0); i < m_nb; ++i)
    {
        for(int j(0); j < m_nb; ++j)
        {
            for(int k(0); k < m_nb; ++k)
            {
                if(i == indexToTurn)
                {
                    m_Framework->pushMatrix();
                    m_Framework->translate(
                                (m_nb*width  + (m_nb-1)*interval)/4 - i*interval + i*width,
                                (m_nb*height + (m_nb-1)*interval)/4 - j*interval + 5*j*height/3,
                                (m_nb*depth  + (m_nb-1)*interval)/4 - k*interval + 5*k*depth/3
                                );
                    m_Framework->rotate(angles[indexToTurn], 1, 0, 0);
                    m_Framework->translate(
                                -((m_nb*width  + (m_nb-1)*interval)/4 - i*interval + i*width),
                                -((m_nb*height + (m_nb-1)*interval)/4 - j*interval + 5*j*height/3),
                                -((m_nb*depth  + (m_nb-1)*interval)/4 - k*interval + 5*k*depth/3)
                                );
                }

                cubeMatrix[i][j][k]->draw();

                if(i == indexToTurn)
                {
                    m_Framework->popMatrix();
                }
            }
        }
    }
}

void Rubbik::addAngle(int _index, float _da)
{
    if(_index < m_nb && xTurning == true || _index >= m_nb && yTurning == true || xTurning == false && yTurning == false)
    {
        angles[_index] += _da;
        indexToTurn = _index;
        if(_index < m_nb)
            xTurning = true;
        else
            yTurning = true;
    }
    if(((angles[_index])%90) == 0)
    {
        xTurning = false;
        yTurning = false;
    }
}
