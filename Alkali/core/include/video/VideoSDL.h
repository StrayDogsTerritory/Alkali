#ifndef ALK_VIDEOSDL_H
#define ALK_VIDEOSDL_H

#include "video/VideoInterface.h"
#include "SDL3/SDL.h"

#include "GL/glew.h"

namespace alk {

	class cVideoSDL : public iVideo
	{
	public:
		cVideoSDL();
		~cVideoSDL();
		bool Init(int alHeight, int alWidth, int alWindowMode);
		bool InitOpenGL();
		
	private:
		SDL_GLContext mGLContext;
		
		SDL_Window* mpSDLWindow;
	};

}
#endif
