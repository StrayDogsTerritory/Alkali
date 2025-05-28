#include "engine/EngineSDL.h"
#include "system/MemoryManager.h"
#include "video/VideoSDL.h"
#include "engine/LogWriter.h"
#include "video/Video.h"

namespace alk {


	cSDLEngine::cSDLEngine()
	{

		mpVideoSDL = alkNew(cVideoSDL, ());

		
	}

	cSDLEngine::~cSDLEngine()
	{
		alkDelete(mpVideoSDL);
	

		Log("SDL modules exit successfully\n");
	}

	cVideo* cSDLEngine::CreateVideoModule()
	{
		cVideo* pVideo = alkNew(cVideo, (mpVideoSDL));

		Log("Video Module Done Init!\n");

		return pVideo;
	}

}

