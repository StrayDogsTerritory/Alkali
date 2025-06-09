#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"

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


		mpSDLWindow = SDL_CreateWindow("Alkali", alWidth, alHeight, mlFlags);
		
		if (mpSDLWindow == NULL)
			FatalError("Error initialising display: %s\n", SDL_GetError());
		
		mGLContext = SDL_GL_CreateContext(mpSDLWindow);

		// init GLEW
		unsigned int GLEWWorks = glewInit();

		Log("Setting up GLEW: ");
		
		if (GLEWWorks == GLEW_OK)
			Log("running\n");
		else
			Error("Glew Failed! Reason: %s\n", glewGetErrorString(GLEWWorks));

		

		mpGraphics->InitOpenGL();

		return true;
	}

	
	SDL_Window* cVideoSDL::GetWindow()
	{
		return mpSDLWindow;
	}
};