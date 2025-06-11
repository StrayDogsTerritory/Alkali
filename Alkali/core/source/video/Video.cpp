#include "video/Video.h"
#include "system/MemoryManager.h"
#include "engine/LogWriter.h"
#include "video/VideoInterface.h"
#include "SDL3/SDL_video.h"

namespace alk {

	cVideo::cVideo(iVideo* apVideo)
	{
		mpVideo = apVideo;
		
	}

	//--------------------------------
	
	cVideo::~cVideo()
	{
		
	}
	bool cVideo::Init(int alHeight, int alWidth, int alWindowMode)
	{
	
		mpVideo->Init(alHeight, alWidth, alWindowMode);

		return true;
	}

	iVideo* cVideo::GetVideo()
	{
		return mpVideo;
	}
}