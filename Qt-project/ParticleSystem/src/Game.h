#ifndef GAME_H
#define GAME_H

#include "qt_framework/GlWindow.h"
#include "Types.h"

class Game : public GlWindow
{
    public:
        Game();
        ~Game();

    protected:
        /*!
        *\brief Initialization des objets.
        */
        bool initializeObjects();

        /*!
        *\brief Rendu de la scène.
        */
        void render();

        void keyPressEvent(QKeyEvent *);
};


#endif
