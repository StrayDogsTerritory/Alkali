#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "video/Video.h"
#include "SDL3/SDL.h"

namespace alk {


	cSDLEngine::cSDLEngine()
	{

		SDL_DisableScreenSaver();
		SDL_HideCursor();


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

