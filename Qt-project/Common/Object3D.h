#ifndef Object3D_h
#define Object3D_h


#include <cmath>
#include "AbstractFramework.h"

class Object3D
{
	public:
        static void setFramework( AbstractFramework* );

	public:
		void draw();

	protected:
		virtual void drawShape() = 0;


	protected:
		static AbstractFramework* m_Framework;
};


#endif
