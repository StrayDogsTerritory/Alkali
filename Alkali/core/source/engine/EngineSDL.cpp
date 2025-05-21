#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"

namespace alk {


	cSDLEngine::cSDLEngine()
	{

		mpVideoSDL = alkNew(cVideoSDL, ());

		
	}


}

