#ifndef TP02_h
#define TP02_h


#include "GlWindow.h"


class TP02 : public GlWindow
{
	public:
        TP02();
        ~TP02();

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
