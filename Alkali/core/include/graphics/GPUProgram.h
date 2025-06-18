#ifndef ALK_GPUPROGRAM_H
#define ALK_GPUPROGRAM_H

#include "system/String.h"

namespace alk {

	enum eGpuProgramType
	{
		eGpuProgramGLSL
	};


	class iGpuProgram
	{
	public:
		iGpuProgram(const tString& asName, eGpuProgramType aeGpuProgramType);
		virtual ~iGpuProgram();

		virtual bool CreateProgram(const twString& asFragFile, const twString& asVertexFile);

		virtual bool Bind();
		virtual bool Link();

		virtual bool Unlink();
		virtual bool Delete();
	private:
		tString msName;
		eGpuProgramType meGpuProgramType;
	};

};
#endif
