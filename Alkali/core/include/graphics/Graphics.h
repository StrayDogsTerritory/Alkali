#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "GL\glew.h"


namespace alk {

	class iVideo;
	class iShader;

	class cGraphics
	{
	public:
		cGraphics();
		~cGraphics();

																																								   
		void DrawTriangle();  // <- this should take an argument in the future, maybe... still deciding how polygons should be used  
		iShader* CreateShader();


	private:
		iVideo* mpVideo;
	};

	

}

#endif
