
#include "SDL3/SDL_video.h"

#include "graphics/GraphicsSDL.h"

namespace alk {

	//temp implementation
	cGraphicsSDL::cGraphicsSDL()
	{
	
	}

	cGraphicsSDL::~cGraphicsSDL()
	{ }

	bool cGraphicsSDL::init()
	{
		SDL_CreateWindow("", 1920, 1080, 1);


		return true;
	}


}