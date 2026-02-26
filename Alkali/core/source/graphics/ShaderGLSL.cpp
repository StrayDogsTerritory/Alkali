#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "system/MemoryManager.h"
#include "system/Platform.h"
#include "engine/LogWriter.h"

namespace alk {

	cGLSLShader::cGLSLShader(const tString& asName, eShaderType aShaderType) : iShader(asName, L"", aShaderType)
	{
		mlShaderID = glCreateShader(ConvertToGL(aShaderType));
	}

	cGLSLShader::~cGLSLShader()
	{
		glDeleteShader(mlShaderID);
	}

	bool cGLSLShader::CreateFromFile(const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"rb");
		fseek(pFile, 0, SEEK_END);
		size_t lSize = ftell(pFile);
		rewind(pFile);

		char* pBuffer = (char*)alkMalloc(sizeof(char)* lSize+1); 
		fread(pBuffer, sizeof(GLchar), lSize, pFile);
		pBuffer[lSize] = 0;
		fclose(pFile);

		bool bRet = CreateFromString(pBuffer);
		alkFree(pBuffer);
		return bRet;
	}

	bool cGLSLShader::CreateFromString(const char* apString)
	{
	//	Log("Shader Source: '%s'\n", apString);

		glShaderSource(mlShaderID, 1, &apString, NULL);

		glCompileShader(mlShaderID);

		GLint lStat;
		glGetShaderiv(mlShaderID, GL_COMPILE_STATUS, &lStat);
		if (lStat == GL_FALSE)
		{
			Error("Failed to compile Shader '%ls'!\n", GetPath().c_str());
			LogShaderError();

			return false;
		}


		return true;
	}

	void cGLSLShader::LogShaderError()
	{
		char* pBuffer;
		GLint BuffSize;
		GLsizei LogLength;

		glGetShaderiv(mlShaderID, GL_INFO_LOG_LENGTH, &BuffSize);
		
		pBuffer = (char*)alkMalloc(BuffSize);
		glGetShaderInfoLog(mlShaderID, BuffSize, &LogLength, pBuffer);
		Log("===========================\n");
		Log("%s", pBuffer);
		Log("==========================\n");
		alkFree(pBuffer);
	}


	GLenum cGLSLShader::ConvertToGL(eShaderType aeShaderType)
	{
		switch (aeShaderType)
		{
		case eShaderType_eVertexShader: return GL_VERTEX_SHADER;
		case eShaderType_ePixelShader: return GL_FRAGMENT_SHADER;
		}
		
		return NULL;
	}
}