#ifndef ALK_GRAPHICSINTERFACE_H
#define ALK_GRAPHICSINTERFACE_H


#include "system/FlagBits.h"
#include "system/String.h"
#include "graphics/Shader.h"

namespace alk {

	class iShader;
	class iGpuProgram;
	class cColour;
	class iVertexBuffer;

	class iGraphics
	{
	public:
		virtual ~iGraphics() {};
		virtual bool Init(int alHeight, int alWidth, int alWindowMode) = 0;
		virtual bool InitOpenGL() = 0;

		virtual iShader* CreateShader(const tString& asName, eShaderType aType)=0;
		virtual iGpuProgram* CreateProgram(const tString& asName)=0;
		virtual iVertexBuffer* CreateVertexBuffer()=0;
		virtual void SwapBuffer()=0;
	

		virtual bool SetCursorVisibility(bool abx) = 0;
		virtual bool SetWindowFullscreen(bool abx) = 0;
		virtual bool SetWindowBorderless(bool abx) = 0;
		virtual bool SetWindowGrabInput(bool abx) = 0;
		
		virtual void SetClearColour(const cColour& aColR) = 0;
		virtual void ClearFrameBuffer(tFlag aClearFlag)=0;
		virtual void FlushRender()=0;
		virtual void SetVSync(bool abx)=0; // fill this later
		virtual void SetRelativeMouse(bool abx)=0;
	};

}
#endif
