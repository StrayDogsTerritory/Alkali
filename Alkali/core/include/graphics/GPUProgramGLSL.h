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


	/*formalize hiarchy here : LAYOUT MUST ALWAYS BE :
	1. Vertex Position
	2. Vertex Normals
	3. Vertex Colour
	4. Vertex UV Coords
	5. Vertex Tangents
	6. Vertex BiNormals
	7. Diffuse Sampler
	8. Normal Sampler
	9. Specular Sampler
	10. Height Sampler
	11. Relief Sampler
	12. Liquid Sampler
	13. RESERVED Sampler
	14. RESERVED Sampler
	15. RESERVED Sampler
	16. RESERVED
	17. RESERVED
	18. RESERVED
	19. RESERVED
	20. RESERVED
	*/

	class cGLSLGpuProgram : public iGpuProgram
	{
	public:
		cGLSLGpuProgram(const tString& asName);
		~cGLSLGpuProgram();

		bool Link();

		void Bind();
		void UnBind();

		 void SetInt(int alIdx,  int alX);
		 void SetFloat(int alIdx,  float afX);
		 void SetVector2f(int alIdx,   tVector2f avX);
		 void SetVector3f(int alIdx, tVector3f avX);
		 void SetMatrixf(int alIdx, tMatrixf amX);

	private:
		std::vector<cGLSLParams> mvGLSLParams;

		static int mlCurrentProgram;
		GLint mlProgramID;
	};
}
#endif