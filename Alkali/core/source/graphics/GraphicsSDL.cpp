#include "graphics/GraphicsSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GpuProgramGLSL.h"

#include "system/Platform.h"
#include "graphics/Shader.h"
#include "graphics/GpuProgram.h"

#include "system/String.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

namespace alk {

	cGraphicsSDL::cGraphicsSDL()
	{
		mbFullscreen = false;
		mpSDLWindow = 0;
	}

	cGraphicsSDL::~cGraphicsSDL()
	{
		SDL_DestroyWindow(mpSDLWindow);
	}

	bool cGraphicsSDL::Init(int alHeight, int alWidth, int alWindowMode)
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

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
			sLog("running\n");
		else
			Error("Glew Failed! Reason: %s\n", glewGetErrorString(lGLEWWorks));

			InitOpenGL();

			SDL_GL_SwapWindow(mpSDLWindow);

		return true;
	}

	bool cGraphicsSDL::InitOpenGL()
	{
		glShadeModel(GL_SMOOTH);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		return true;


	}

	iShader* cGraphicsSDL::CreateShader(const tString& asName, eShaderType aType)
	{
		return alkNew(cGLSLShader, (asName, aType));
	}

	iGpuProgram* cGraphicsSDL::CreateProgram(const tString& asName)
	{
		return alkNew(cGLSLGpuProgram, (asName));
	}


	void cGraphicsSDL::SwapBuffer()
	{
		SDL_GL_SwapWindow(mpSDLWindow);
	}

	bool cGraphicsSDL::SetCursorVisibility(bool abx)
	{
		
		return abx ? SDL_ShowCursor() : SDL_HideCursor();
	}


	bool cGraphicsSDL::SetWindowFullscreen(bool abx)
	{
		return abx ? SDL_SetWindowFullscreen(mpSDLWindow, true) : SDL_SetWindowFullscreen(mpSDLWindow, false);
	}

	bool cGraphicsSDL::SetWindowBorderless(bool abx)
	{
		if (!mbFullscreen)
			 abx ? SDL_SetWindowFullscreen(mpSDLWindow, true) : SDL_SetWindowFullscreen(mpSDLWindow, false);
		
		return abx ? SetWindowGrabInput(true) : SetWindowGrabInput(false);
	}

	bool cGraphicsSDL::SetWindowGrabInput(bool abx)
	{
		//Log("the func ran\n");
		return abx ? SDL_SetWindowMouseGrab(mpSDLWindow, false) && SDL_SetWindowKeyboardGrab(mpSDLWindow, false)
			: SDL_SetWindowMouseGrab(mpSDLWindow, true) && SDL_SetWindowKeyboardGrab(mpSDLWindow, true);
	}



};