#ifndef TP02_Grue_h
#define TP02_Grue_h


#include "GlWindow.h"


class TP02_Grue : public GlWindow
{
    public:
        TP02_Grue();
        ~TP02_Grue();

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
};


#endif
