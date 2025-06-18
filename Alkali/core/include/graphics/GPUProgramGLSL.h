#ifndef ALK_GPUPROGRAMGLSL_H
#define ALK_GPUPROGRAMGLSL_H
#include "GL/glew.h"
#include "graphics/GPUProgram.h"
#include "graphics/ShaderGLSL.h"
#include "system/String.h"

namespace alk {

	class cGLSLGpuProgram : iGpuProgram
	{
	public:
		cGLSLGpuProgram(const tString& asName, iShader* apVertexShader, iShader* apPixelShader);
		~cGLSLGpuProgram();

		 bool CreateProgram(const twString& asFragFile, const twString& asVertexFile);

		 bool Bind();
		 bool Link();

		 bool Unbind();

	};
}
#endif