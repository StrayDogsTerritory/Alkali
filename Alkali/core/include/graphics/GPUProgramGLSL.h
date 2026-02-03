#ifndef ALK_GPUPROGRAMGLSL_H
#define ALK_GPUPROGRAMGLSL_H

#include "GL/glew.h"
#include "graphics/GPUProgram.h"
#include "graphics/ShaderGLSL.h"
#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace alk {

	class cGLSLParams
	{
	public:
		cGLSLParams(tString asName, GLint alIdx) : msName(asName), mlIdx(alIdx) {}

		tString msName;
		GLint mlIdx;
	};


	class cGLSLGpuProgram : public iGpuProgram
	{
	public:
		cGLSLGpuProgram(const tString& asName);
		~cGLSLGpuProgram();

		bool Link();

		void Bind();
		void UnBind();

		 void SetInt(int alIdx, const int& alX);
		 void SetFloat(int alIdx, const float& afX);
		 void SetVector2f(int alIdx, const  tVector2f& avX);
		 void SetVector3f(int alIdx, const tVector3f& avX);
		 void SetMatrixf(int alIdx, const tMatrixf& amX);

	private:
		std::vector<cGLSLParams> mvGLSLParams;

		static int mlCurrentProgram;
		GLint mlProgramID;
	};
}
#endif