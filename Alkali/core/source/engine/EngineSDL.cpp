#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "video/Video.h"

#include "SDL3/SDL.h"


namespace alk {


	cSDLEngine::cSDLEngine()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			FatalError("Failed to init Video: %s", SDL_GetError());
		}

		SDL_DisableScreenSaver();


   		mpVideoSDL = alkNew(cVideoSDL, ());

		
	}

	cSDLEngine::~cSDLEngine()
	{
		alkDelete(mpVideoSDL);
	

		
	}

	cVideo* cSDLEngine::CreateVideoModule()
	{
		cVideo* pVideo = alkNew(cVideo, (mpVideoSDL));

		

		return pVideo;
	}

}

