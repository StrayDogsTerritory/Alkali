#include "graphics/GPUProgram.h"
#include "graphics/Shader.h"



namespace alk {

	iGpuProgram::iGpuProgram(const tString& asName, eGpuProgramType aeGpuProgramType)
	{
		msName = asName;
		meGpuProgramType = aeGpuProgramType;

			for (int i = 0; i < 2; ++i)
				mpShader[i] =NULL;

	}

	void iGpuProgram::SetShaderType(eShaderType aeShaderType, iShader* apShader)
	{
		 mpShader[aeShaderType] = apShader;
	}
}