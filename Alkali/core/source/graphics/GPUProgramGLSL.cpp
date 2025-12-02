#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"

#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "engine/LogWriter.h"

namespace alk {

	cGLSLGpuProgram::cGLSLGpuProgram(const tString& asName)
		: iGpuProgram(asName, eGpuProgramType_GLSL)
	{
		mlProgramID = glCreateProgram();
	}

	cGLSLGpuProgram::~cGLSLGpuProgram()
	{
		for (int i = 0; i < 2; ++i)
		{
			cGLSLShader* pShader = static_cast<cGLSLShader*>(mpShader[i]);
			if (pShader)
			{
				glDetachShader(mlProgramID, pShader->GetHandle());
			}
		}
		glDeleteProgram(mlProgramID);
	}

	bool cGLSLGpuProgram::Link()
	{
		for (int i = 0; i < 2; ++i)
		{
			cGLSLShader* pShader = static_cast<cGLSLShader*>(mpShader[i]);
			if (pShader)
			{
				glAttachShader(mlProgramID, pShader->GetHandle());
			}
		}

		glLinkProgram(mlProgramID);

		GLint lStatus;
		glGetProgramiv(mlProgramID, GL_LINK_STATUS, &lStatus);
		if (lStatus == GL_FALSE)
		{
			Error("Program '%s' Could not be linked!\n", msName.c_str());
		}
		
		return true;
	}

	void cGLSLGpuProgram::Bind()
	{
		glUseProgram(mlProgramID);
	}

	void cGLSLGpuProgram::UnBind()
	{
		glUseProgram(0);
	}
}