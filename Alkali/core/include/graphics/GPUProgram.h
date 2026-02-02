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
		eGpuProgramType_HLSL,
		eGpuProgramType_Last_Enum
	};


	class iGpuProgram
	{
	public:
		iGpuProgram(const tString& asName, eGpuProgramType aProgramType);
		virtual ~iGpuProgram();

		tString GetName() { return msName; }

		 void SetShader(iShader* apShader, eShaderType aShaderType);
		 iShader* GetShader(eShaderType aType) { return mpShader[aType]; }

		 virtual bool Link()=0;
		 
		 virtual void Bind()=0;
		 virtual void UnBind()=0;

		 virtual void SetInt()=0;
		 virtual void SetFloat() = 0;
		 virtual void SetVector2f() = 0;
		 virtual void SetVector3f() = 0;
		virtual void SetMatrixf() = 0;

	protected:
		tString msName;
		eGpuProgramType mProgramType;
		iShader* mpShader[2];
	};

};
#endif
