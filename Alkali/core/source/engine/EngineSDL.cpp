#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "video/Video.h"
#include "SDL3/SDL.h"

namespace alk {


	cSDLEngine::cSDLEngine(tFlag alEngineSetupFlags)
	{

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			FatalError("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			exit(1);
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

