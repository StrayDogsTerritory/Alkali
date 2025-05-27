#include "video/VideoSDL.h"

namespace alk {

	cVideoSDL::cVideoSDL()
	{
	}

	cVideoSDL::~cVideoSDL()
	{
	}

	bool cVideoSDL::Init(int alHeight, int alWidth, bool abIsFullScreen)
	{
		mpSDLWindow = SDL_CreateWindow("Alkali", alWidth, alHeight, 0);

		mbWorked = true;

		return true;
	}

};