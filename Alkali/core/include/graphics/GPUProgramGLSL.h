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

		bool Link();

		void Bind();
		void UnBind();

		 void SetInt();
		 void SetFloat();
		 void SetVector2f();
		 void SetVector3f();
		 void SetMatrixf();

	private:
		static int mlCurrentProgram;
		GLint mlProgramID;
	};
}
#endif