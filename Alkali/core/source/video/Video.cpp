#include "video/Video.h"
#include "system/MemoryManager.h"
#include "engine/LogWriter.h"
#include "video/VideoInterface.h"


namespace alk {

	cVideo::cVideo(iVideo* apVideo)
	{
		mpiVideo = apVideo;
		Log("video.cpp loaded\n");
	}

	//--------------------------------

	cVideo::~cVideo()
	{
	
	}
	bool cVideo::Init(int alHeight, int alWidth, int alWindowMode)
	{
	
		mpiVideo->Init(alHeight, alWidth, alWindowMode);

		return true;
	}
}