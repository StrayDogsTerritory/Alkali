#include "graphics/Graphics.h"
#include "video/VideoSDL.h"
#include "system/MemoryManager.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"
#include "engine/LogWriter.h"



namespace alk {

	cGraphics::cGraphics(tFlag alShadingLanguage)
	{ 
		
	}

	cGraphics::~cGraphics()
	{
	
	}

	iShader* cGraphics::CreateShader(const tString& asName, eShaderType aeShaderType)
	{
		
		return alkNew(cGLSLShader, (asName, aeShaderType));
	}

	iProgram* cGraphics::CreateProgram()
	{
		return nullptr;
	}








}