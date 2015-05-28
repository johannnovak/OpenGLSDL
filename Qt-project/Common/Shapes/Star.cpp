#include "Star.h"

Star::Star(float nbBranch, float width, float innerRadius,float outerRadius)
{
    this->nbBranch = nbBranch;
    this->width = width;
    this->innerRadius = innerRadius;
    this->outerRadius = outerRadius;
}

void Star::drawShape()
{
    float nbSide = 0;
    float intersectionBranchNb = nbBranch-1;
    float innerAngle = M_PI / intersectionBranchNb;

    int sizeInner = (nbBranch+1)*3;
    int sizeOuter = (intersectionBranchNb+1)*3;
    int totalSize = (sizeInner*2) + sizeOuter;

    float outerCirclePosition[sizeOuter];
    float innerCirclePosition[sizeInner*2];

    float outerCircleColor[sizeOuter];
    float innerCircleColor[sizeInner*2];

    float totalPosition[totalSize];
    float totalColor[totalSize];

    for(int i(0); i < sizeOuter; i += 3)
    {
        outerCirclePosition[i+0] = (innerRadius + outerRadius) * cos(2 * M_PI * nbSide / nbBranch);
        outerCirclePosition[i+1] = (innerRadius + outerRadius) * sin(2 * M_PI * nbSide / nbBranch);
        outerCirclePosition[i+2] = 0;

        outerCircleColor[i+0] = 0.5;
        outerCircleColor[i+1] = 0.5;
        outerCircleColor[i+2] = 0.5;

        ++nbSide;
    }

    nbSide = 0;
    for(int i(0); i < sizeInner * 2; i += 6)
    {
        innerCirclePosition[i+0] = (innerRadius) * cos((2 * M_PI * nbSide / nbBranch) + innerAngle);
        innerCirclePosition[i+1] = (innerRadius) * sin((2 * M_PI * nbSide / nbBranch) + innerAngle);
        innerCirclePosition[i+2] = width;
        innerCirclePosition[i+3] = (innerRadius) * cos((2 * M_PI * nbSide / nbBranch) + innerAngle);
        innerCirclePosition[i+4] = (innerRadius) * sin((2 * M_PI * nbSide / nbBranch) + innerAngle);
        innerCirclePosition[i+5] = -width;

        innerCircleColor[i+0] = 0.8;
        innerCircleColor[i+1] = 0;
        innerCircleColor[i+2] = 0;
        innerCircleColor[i+3] = 0.3;
        innerCircleColor[i+4] = 0;
        innerCircleColor[i+5] = 0.3;

        ++nbSide;
    }

    int j = 0;
    int k = 0;
    for(int i(0); i < totalSize; i += 9)
    {
        totalPosition[i+0] = outerCirclePosition[j+0];
        totalPosition[i+1] = outerCirclePosition[j+1];
        totalPosition[i+2] = outerCirclePosition[j+2];

        totalPosition[i+3] = innerCirclePosition[k+0];
        totalPosition[i+4] = innerCirclePosition[k+1];
        totalPosition[i+5] = innerCirclePosition[k+2];
        totalPosition[i+6] = innerCirclePosition[k+3];
        totalPosition[i+7] = innerCirclePosition[k+4];
        totalPosition[i+8] = innerCirclePosition[k+5];

        totalColor[i+0] = outerCircleColor[j+0];
        totalColor[i+1] = outerCircleColor[j+1];
        totalColor[i+2] = outerCircleColor[j+2];

        totalColor[i+3] = innerCircleColor[k+0];
        totalColor[i+4] = innerCircleColor[k+1];
        totalColor[i+5] = innerCircleColor[k+2];
        totalColor[i+6] = innerCircleColor[k+3];
        totalColor[i+7] = innerCircleColor[k+4];
        totalColor[i+8] = innerCircleColor[k+5];

        j = j + 3;
        k = k + 6;
    }

    GLint shaderPositionID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint shaderColorID = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(shaderPositionID);
    glEnableVertexAttribArray(shaderColorID);

    glVertexAttribPointer(shaderPositionID, GL_FLOAT, 3, GL_FALSE, 0, totalPosition);
    glVertexAttribPointer(shaderColorID, GL_FLOAT, 3, GL_FALSE, 0, totalColor);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, totalSize+1);

    glDisableVertexAttribArray(shaderPositionID);
    glDisableVertexAttribArray(shaderColorID);
}
