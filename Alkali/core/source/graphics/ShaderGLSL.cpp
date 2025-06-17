#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "system/MemoryManager.h"
#include "system/Platform.h"

#include "io.h"

namespace alk {

	cGLSLShader::cGLSLShader(const tString& asShader, eShaderType aeShaderType, cGLSLShader* pShader)
	{
		msName = asShader;
		meShaderType = aeShaderType;

	mlShaderID = glCreateShader(GetShaderType(aeShaderType)); 

	}
 

	cGLSLShader::~cGLSLShader()
	{
		DestroyShader(this);
	}

	bool cGLSLShader::CreateShader(const twString& asShader, eShaderType aeShaderType, iShader* pShader)
	{
		
		FILE *pFile = cPlatform::OpenFile(asShader, L"rb");

		fseek(pFile, 0, SEEK_END);
		int lFileSize = ftell(pFile);
		rewind(pFile);

		char* pBuffer = (char*) alkMalloc(lFileSize);
		
		pBuffer[lFileSize] = 0; // null terminate the string

		fclose(pFile);

		glShaderSource(mlShaderID, 1, &pBuffer,	NULL);
		glCompileShader(mlShaderID);

		alkFree(pBuffer);

		return true;

	}

	void cGLSLShader::DestroyShader(iShader* apShader)
	{
		glDeleteShader(mlShaderID);
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


	GLenum cGLSLShader::GetShaderType(eShaderType aeShaderType)
	{
		switch (aeShaderType)
		{
			case eVertexShader:
				return GL_VERTEX_SHADER;
				break;
			case ePixelShader:
				return GL_FRAGMENT_SHADER;
		}
	}
}