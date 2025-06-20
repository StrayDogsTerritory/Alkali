#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "GL\glew.h"
#include "system/FlagBits.h"
#include "system/String.h"

namespace alk {

	class iVideo;
	class iShader;
	class iProgram;

	class cGraphics
	{
	public:
		cGraphics(tFlag alShadingLanguage);
		~cGraphics();
 
		iShader* CreateShader();
		iProgram* CreateProgram();


	private:
		iVideo* mpVideo;
		unsigned int mlShadingLanguage; // remove this of i never add dx support
	};

	

}

#endif
