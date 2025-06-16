#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "system/MemoryManager.h"
#include "system/Platform.h"

namespace alk {

	cGLSLShader::cGLSLShader(const tString& asShader, eShaderType aeShaderType, cGLSLShader* pShader)
	{
		msName = asShader;
		meShaderType = aeShaderType;

	mlShaderID = glCreateShader(aeShaderType); 

	}
 

	cGLSLShader::~cGLSLShader()
	{
		glDeleteShader(mlShaderID);
	}

	bool cGLSLShader::CreateShader(const twString& asShader, eShaderType aeShaderType, iShader* pShader)
	{
		//something crazy up here
		cPlatform::OpenFile(asShader)


		glShaderSource(mlShaderID, 1, );

		glCompileShader(mlShaderID);

		return true;
	}

	void cGLSLShader::DestroyShader(iShader* apShader)
	{
		
	}

	/*bool cGLSLShader::CompileShader(iShader* pShader)
	{
		glCompileShader(mlShaderID);

		return false;
	}*/

	[[depricated]]
	bool cGLSLShader::ReloadShader()
	{
		///////////////////////////
		// not safe, don't run yet

		glDeleteShader(mlShaderID);
		glCreateShader(mlShaderID);

		return true;
	}


}