#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "graphics/GraphicsSDL.h"
#include "engine/LogWriter.h"
#include "graphics/Graphics.h"

#include "SDL3/SDL.h"

#include "system/FlagBits.h"
#include "system/SystemSDL.h"
#include "system/System.h"

#include "input/InputSDL.h"
#include "input/Input.h"

namespace alk {


	cSDLEngine::cSDLEngine(tFlag alSetupFlags)
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			FatalError("Failed to init Video: %s", SDL_GetError());
		}

		SDL_DisableScreenSaver();


   		mpGraphicsSDL = alkNew(cGraphicsSDL, ());
		mpSystemSDL = alkNew(cSystemSDL, ());
		mpInputSDL = alkNew(cInputSDL, (mpGraphicsSDL));
	}

	cSDLEngine::~cSDLEngine()
	{
		alkDelete(mpGraphicsSDL);	
		alkDelete(mpSystemSDL);
		alkDelete(mpInputSDL);
	}

	cGraphics* cSDLEngine::CreateGraphicsModule()
	{
		cGraphics* pGraphics = alkNew(cGraphics, (mpGraphicsSDL));
		return pGraphics;
	}

	cSystem* cSDLEngine::CreateSystemModule()
	{
		cSystem* pSystem = alkNew(cSystem, (mpSystemSDL));
		return pSystem;
	}
	cInput* cSDLEngine::CreateInputModule()
	{
		cInput* pInput = alkNew(cInput, (mpInputSDL));
		return pInput;
	}
}

