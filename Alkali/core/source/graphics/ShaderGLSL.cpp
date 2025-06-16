#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "system/MemoryManager.h"

namespace alk {

	cGLSLShader::cGLSLShader(const tString& asShader, eShaderType aeShaderType, cGLSLShader* pShader)
	{
		msName = asShader;
		meShaderType = aeShaderType;

		glCreateShader(aeShaderType); 

	}

	cGLSLShader::~cGLSLShader()
	{
		alkDelete(this);
	}

	bool cGLSLShader::CreateShader(eShaderType aeShaderType)
	{
		return true;
	}

	void cGLSLShader::DestroyShader(iShader* apShader)
	{
		
	}

	bool cGLSLShader::CompileShader(iShader* pShader)
	{
	//	glCompileShader();

		return false;
	}

	[[depricated]]
	bool cGLSLShader::ReloadShader()
	{
		///////////////////////////
		// not safe, don't run yet

		DestroyShader(this);
		CreateShader(meShaderType);

		return true;
	}


}