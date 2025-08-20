#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"
#include "graphics/ShaderGLSL.h"

#include "system/Platform.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

namespace alk {

	cVideoSDL::cVideoSDL()
	{
		mbFullscreen = false;
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

		SetCursorVisibility(true);
		//SetWindowBorderless(true);

		mGLContext = SDL_GL_CreateContext(mpSDLWindow);

		// init GLEW
		unsigned int lGLEWWorks = glewInit();

		Log("Setting up GLEW: ");

		if (lGLEWWorks == GLEW_OK)
			Log("running\n");
		else
			Error("Glew Failed! Reason: %s\n", glewGetErrorString(lGLEWWorks));

			InitOpenGL();

		return true;
	}

	bool cVideoSDL::InitOpenGL()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);

		//float vVerts[] = {
		//	0.0f, 0.5f, 0.0f,
		//	-0.5f, -0.5f, 0.0f,
		//	0.5f, -0.5f, 0.0f

		//};


		//glClear(GL_COLOR_BUFFER_BIT);

		//glEnableClientState(GL_VERTEX_ARRAY);
		////glEnableClientState(GL_COLOR_ARRAY);
		//glVertexPointer(3, GL_FLOAT, 0, vVerts);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//mpGraphics->CreateProgramWithShaders("test", "TestFrag.glsl", "TestVert.glsl");

		SwapBuffer();

		return true;


	}

	

	void cVideoSDL::SwapBuffer()
	{
		SDL_GL_SwapWindow(mpSDLWindow);
	}

	bool cVideoSDL::SetCursorVisibility(bool abx)
	{
		
		return abx ? SDL_ShowCursor() : SDL_HideCursor();
	}


	bool cVideoSDL::SetWindowFullscreen(bool abx)
	{
		return abx ? SDL_SetWindowFullscreen(mpSDLWindow, true) : SDL_SetWindowFullscreen(mpSDLWindow, false);
	}

	bool cVideoSDL::SetWindowBorderless(bool abx)
	{
		if (!mbFullscreen)
			 abx ? SDL_SetWindowFullscreen(mpSDLWindow, true) : SDL_SetWindowFullscreen(mpSDLWindow, false);
		
		return abx ? SetWindowGrabInput(true) : SetWindowGrabInput(false);
	}

	bool cVideoSDL::SetWindowGrabInput(bool abx)
	{
		//Log("the func ran\n");
		return abx ? SDL_SetWindowMouseGrab(mpSDLWindow, false) && SDL_SetWindowKeyboardGrab(mpSDLWindow, false)
			: SDL_SetWindowMouseGrab(mpSDLWindow, true) && SDL_SetWindowKeyboardGrab(mpSDLWindow, true);
	}



};