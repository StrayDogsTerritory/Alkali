#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "graphics/GraphicsSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"

#include "SDL3/SDL.h"
#include "system/FlagBits.h"

namespace alk {


	cSDLEngine::cSDLEngine(tFlag alSetupFlags)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			FatalError("Failed to init Video: %s", SDL_GetError());
		}

		SDL_DisableScreenSaver();


   		mpGraphicsSDL = alkNew(cGraphicsSDL, ());

		
	}

	cSDLEngine::~cSDLEngine()
	{
		alkDelete(mpGraphicsSDL);	
	}

	cGraphics* cSDLEngine::CreateGraphicsModule()
	{
		cGraphics* pGraphics = alkNew(cGraphics, (mpGraphicsSDL));

		

		return pGraphics;
	}

}

