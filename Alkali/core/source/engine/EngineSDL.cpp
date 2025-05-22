#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"

namespace alk {


	cSDLEngine::cSDLEngine()
	{

		mpVideoSDL = alkNew(cVideoSDL, ());

		
	}

	cSDLEngine::~cSDLEngine()
	{
	
	
	}

	cVideoSDL* cSDLEngine::CreateVideoModule()
	{
		cVideoSDL* pVideoSDL = alkNew(cVideoSDL, ());

		return pVideoSDL;
	}

}

