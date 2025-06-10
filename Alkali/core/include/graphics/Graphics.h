#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "GL\glew.h"


namespace alk {

	class cVideoSDL;

	class cGraphics
	{
	public:
		cGraphics();
		~cGraphics();

		bool InitOpenGL();																																										   
		void DrawTriangle();  // <- this should take an argument in the future, maybe... still deciding how polygons should be used  

	};

	cVideoSDL* mpVideoSDL;

}

#endif
