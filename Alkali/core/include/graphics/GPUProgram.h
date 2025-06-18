#ifndef ALK_GPUPROGRAM_H
#define ALK_GPUPROGRAM_H

#include "system/String.h"

namespace alk {

	class iShader;

	enum eGpuProgramType
	{
		eGpuProgramGLSL,
		Last_Enum
	};


	class iGpuProgram
	{
	public:
		iGpuProgram(const tString& asName, eGpuProgramType aeGpuProgramType);
		iShader* GetShaderType(iShader* apShader);

		virtual ~iGpuProgram() ;


		virtual bool Bind()=0;
		virtual bool Link()=0;

		virtual bool Unbind()=0;

		

	private:
		tString msName;
		eGpuProgramType meGpuProgramType;
		iShader* mpShader[2];
	};

};
#endif
