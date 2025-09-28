#include "graphics/GPUProgram.h"
#include "graphics/Shader.h"



namespace alk {

	iGpuProgram::iGpuProgram(const tString& asName, eGpuProgramType aType)
	{
		msName = asName;
		mProgramType = aType;

		for (int i = 0; i < 2; ++i) mpShader[i] = NULL;
	}

	iGpuProgram::~iGpuProgram()
	{

	}

	void iGpuProgram::SetShader(iShader* apShader, eShaderType aShaderType)
	{
		mpShader[aShaderType] = apShader;
	}

}