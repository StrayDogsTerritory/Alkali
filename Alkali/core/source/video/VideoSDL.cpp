#include "video/VideoSDL.h"
#include "engine/LogWriter.h"

namespace alk {

	cVideoSDL::cVideoSDL()
	{
		mpSDLWindow = 0;
	}

	cVideoSDL::~cVideoSDL()
	{
		SDL_DestroyWindow(mpSDLWindow);
	}

	bool cVideoSDL::Init(int alHeight, int alWidth, int alWindowMode)
	{

		unsigned int mlFlags = SDL_WINDOW_OPENGL;


		mpSDLWindow = SDL_CreateWindow("Alkali", alWidth, alHeight, alWindowMode);
		
		if (mpSDLWindow == NULL)
			FatalError("Error initialising display: %s\n", SDL_GetError());
		
		mGLContext = SDL_GL_CreateContext(mpSDLWindow);

		return true;
	}

};