#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"

#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"

namespace alk {


	cGLSLGpuProgram::cGLSLGpuProgram(const tString& asName) : iGpuProgram(asName, eGpuProgramType_GLSL)
	{
		mlProgramID = glCreateProgram();
	}

	cGLSLGpuProgram::~cGLSLGpuProgram()
	{


		for (int i = 0; i < 2; ++i)
		{
			cGLSLShader* pGLSLShader = static_cast<cGLSLShader*> (mpShader[i]);

			if (pGLSLShader)
			{
				glDetachShader(mlProgramID, pGLSLShader->GetShaderID());
			}
		}

		glDeleteProgram(mlProgramID);
	}

	bool cGLSLGpuProgram::Link()
	{
		for (int i = 0; i < 2; ++i)
		{
			cGLSLShader* pGLSLShader = static_cast<cGLSLShader*> (mpShader[i]);

			if (pGLSLShader)
			{
				glAttachShader(mlProgramID, pGLSLShader->GetShaderID());
			}
		}

		glLinkProgram(mlProgramID);

		return true;
	}

}