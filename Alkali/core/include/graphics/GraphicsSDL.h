#ifndef ALK_GRAPHICSSDL_H
#define ALK_GRAPHICSSDL_H

#include "graphics/GraphicsInterface.h"
#include "graphics/VertexBuffer.h"

#include "system/FlagBits.h"

#include "SDL3/SDL.h"

#include "GL/glew.h"
#include "GL/wglew.h" // is this necessary?

namespace alk {

	class cGraphics;
	class iShader;
	class iGpuProgram;
	class iVertexBuffer;
	class iTexture;

	class cGraphicsSDL : public iGraphics
	{
	public:
		cGraphicsSDL();
		~cGraphicsSDL();
		bool Init(int alHeight, int alWidth, int alWindowMode);
		bool InitOpenGL();

		void LogGPUInfo();
		int GetCardMaxes(eGpuMaximum aGpuMaxes);

		iShader* CreateShader(const tString& asName, eShaderType aType);
		iGpuProgram* CreateProgram(const tString& asName);
		iVertexBuffer* CreateVertexBuffer(eVertexBufferDrawType aDrawType, eVertexBufferPrimitiveAssemblyType aPrimAssemblyType);
		iTexture* CreateTexture(const tString& asName);

		void SwapBuffer(); // don't call it SwapBuffers cuz windows gets all weird about it.
		void FlushRender();
		void ClearFrameBuffer(tFlag aClearFlag);

		bool SetCursorVisibility(bool abx);
		bool SetWindowFullscreen(bool abx);
		bool SetWindowBorderless(bool abx);
		bool SetWindowGrabInput(bool abx);
		void SetVSync(bool abx);

		void SetClearColour(const cColour& aCol);
		void SetRelativeMouse(bool abX);
	private:
		SDL_GLContext mGLContext;
		SDL_Window* mpSDLWindow;
		cGraphics* mpGraphics;

		bool mbFullscreen;
	};

	
}
#endif
