#include "graphics/GraphicsSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GpuProgramGLSL.h"

#include "system/Platform.h"
#include "graphics/Shader.h"
#include "graphics/GpuProgram.h"
#include "graphics/Colour.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferGL.h"

#include "system/String.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

namespace alk {

	cGraphicsSDL::cGraphicsSDL()
	{
		mbFullscreen = true;
		mpSDLWindow = NULL;
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

		unsigned int mlFlags = SDL_WINDOW_OPENGL; // | SDL_WINDOW_FULLSCREEN;


		mpSDLWindow = SDL_CreateWindow("Alkali", alWidth, alHeight, mlFlags);
		if (mpSDLWindow == NULL)
			FatalError("Error initialising display: %s\n", SDL_GetError());

		SetCursorVisibility(true);
		//SetWindowFullscreen(true);
		//SetWindowBorderless(true);
		mGLContext = SDL_GL_CreateContext(mpSDLWindow);

		// init GLEW
		unsigned int lGLEWWorks = glewInit();

		Log("Setting up GLEW: ");

		if (lGLEWWorks == GLEW_OK)
			Log("running\n");
		else
			FatalError("Glew Failed! Reason: %s\n", glewGetErrorString(lGLEWWorks));

		InitOpenGL();

		SDL_GL_SwapWindow(mpSDLWindow);

		return true;
	}

	bool cGraphicsSDL::InitOpenGL()
	{
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_ALPHA_TEST);
		glDepthMask(true);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		/*glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_EDGE_FLAG_ARRAY);*/


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

	iVertexBuffer* cGraphicsSDL::CreateVertexBuffer()
	{
		return alkNew(cVertexBufferGL, ());
	}


	void cGraphicsSDL::SwapBuffer()
	{
		SDL_GL_SwapWindow(mpSDLWindow);
	}

	void cGraphicsSDL::FlushRender()
	{
		glFlush();
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

	void cGraphicsSDL::SetVSync(bool abx)
	{
		SDL_GL_SetSwapInterval(abx ? 0 : 1);
	}

	void cGraphicsSDL::SetClearColour(const cColour& aCol)
	{
		
		glClearColor(aCol.r, aCol.g, aCol.b, aCol.a);
	}



};