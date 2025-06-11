#ifndef ALK_VIDEOSDL_H
#define ALK_VIDEOSDL_H

#include "video/VideoInterface.h"
#include "SDL3/SDL.h"

#include "GL/glew.h"
#include "GL/wglew.h"

namespace alk {

	class cGraphics;


	class cVideoSDL : public iVideo
	{
	public:
		cVideoSDL();
		~cVideoSDL();
		bool Init(int alHeight, int alWidth, int alWindowMode);
		bool InitOpenGL();

		void SwapBuffer();
		
	private:
		SDL_GLContext mGLContext;
		SDL_Window* mpSDLWindow;
		cGraphics* mpGraphics;
	};

	
}
#endif
