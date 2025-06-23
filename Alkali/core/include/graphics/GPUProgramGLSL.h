#ifndef ALK_GPUPROGRAMGLSL_H
#define ALK_GPUPROGRAMGLSL_H
#include "GL/glew.h"
#include "graphics/GPUProgram.h"
#include "graphics/ShaderGLSL.h"
#include "system/String.h"

namespace alk {

	class cGLSLGpuProgram : public iGpuProgram
	{
	public:
		cGLSLGpuProgram(const tString& asName);
		~cGLSLGpuProgram();


		 bool Bind();
		 bool Link();

		 bool Unbind();
	private:
		GLint mlProgramID;
		tString asName;
	};
}
#endif