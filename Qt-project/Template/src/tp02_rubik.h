#ifndef TP02_Rubbik_h
#define TP02_Rubbik_h


#include "GlWindow.h"
#include "Shapes/Axis.h"
#include "Shapes/rubbik.h"

class TP02_Rubbik : public GlWindow
{
    public:
        TP02_Rubbik();
        ~TP02_Rubbik();

        /*!
        *\brief Initialization des objets.
        */
        bool initializeObjects();

        /*!
        *\brief Rendu de la scène.
        */
        void render();

        void createAxis();

        void keyPressEvent(QKeyEvent *);
private :
        float m_camangle1;
        float m_camangle2;
        Axis* m_axis;
        Rubbik* m_rubbik;
        Cube** m_cube;
        Cube* m_cube1;
        Cube* m_cube2;
};


#endif
