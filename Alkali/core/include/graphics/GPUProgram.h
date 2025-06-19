#ifndef ALK_GPUPROGRAM_H
#define ALK_GPUPROGRAM_H

#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "system/String.h"

namespace alk {

	class iShader;

	enum eGpuProgramType
	{
		eGpuProgramType_GLSL,
		eGpuProgramType_Last_Enum
	};


	class iGpuProgram
	{
	public:
		iGpuProgram(const tString& asName, eGpuProgramType aeGpuProgramType);
		void SetShaderType(eShaderType aeShaderType, iShader* apShader);

		virtual ~iGpuProgram() ;


		virtual bool Bind()=0;
		virtual bool Link()=0;

		virtual bool Unbind()=0;

		

	protected:
		tString msName;
		eGpuProgramType meGpuProgramType;
		iShader* mpShader[2];
	};

};
#endif
