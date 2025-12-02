#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "GL\glew.h"
#include "system/FlagBits.h"
#include "system/String.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"

#include "math/Vector3.h"

#include <list>

namespace alk {

	class iGraphics;
	class iShader;
	class iGpuProgram;
	class cResources;
	class iVertexBuffer;

	typedef std::list<iGpuProgram*> tlProgramList;
	typedef tlProgramList::iterator tlProgramListIt;

	class cGraphics
	{
	public:
		cGraphics(iGraphics* apGraphics);
		~cGraphics();
 
		bool Init(cResources* apResources, int alHeight, int alWidth, int alWindowMode);

		iGraphics* GetLowGraphics() { return mpGraphics; }

		iGpuProgram* CreateProgram(const tString& asName);

		iGpuProgram* CreateShaderProgram(const tString& asName, const tString& asPixShader, const tString& asVertShader);

		iVertexBuffer* CreateTempVtxBuffer(tVector3f avSize);

		int GetBoxIdx(int i, int x, int y, int z);

	private:
		tlProgramList lProgramList;
		iGraphics* mpGraphics;
		cResources* mpResources;
	};

	

}

#endif
