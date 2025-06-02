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
		mpSDLWindow = SDL_CreateWindow("Alkali", alWidth, alHeight, alWindowMode);


		Log("Init Window finished!\n");
		
		return true;
	}

};