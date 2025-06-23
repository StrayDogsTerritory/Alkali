#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "GL\glew.h"
#include "system/FlagBits.h"
#include "system/String.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"

namespace alk {

	class iVideo;
	class iShader;
	class iGpuProgram;

	class cGraphics
	{
	public:
		cGraphics(tFlag alShadingLanguage);
		~cGraphics();
 
		iShader* CreateShader(const tString& asName, eShaderType aeShaderType);
		iGpuProgram* CreateProgram( const tString &asName);

		// kinda temporary, fix it later 
		iShader* CreateShaderDifferentAndTemp(const tString& asName, eShaderType aeShaderType);
		iGpuProgram* CreateProgramWithShaders( const tString &asName, const tString& asPixelShader, const tString& asVertexShader);

	private:
		iVideo* mpVideo;
		unsigned int mlShadingLanguage; // remove this of i never add dx support
	};

	

}

#endif
