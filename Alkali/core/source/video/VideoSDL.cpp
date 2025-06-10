<<<<<<< HEAD
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

		SDL_GL_SwapWindow(mpSDLWindow);

		return true;
	}

	

=======
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

	
<<<<<<< HEAD

>>>>>>> parent of e1637d2 (technically broken, need to add buffer swapping manually, because for some reason the screen pointer hates me. Fuck you screen pointer, make my life easier you shitty little thing. Fuck you so much you pathetic little pointer.)
=======
	SDL_Window* cVideoSDL::GetWindow()
	{
		return mpSDLWindow;
	}
>>>>>>> e1637d263fa7994d5ce3a7276463df609a269e2f
>>>>>>> d9dde0ee5dadd39e1b8cc25b534e2432db9054c2
};