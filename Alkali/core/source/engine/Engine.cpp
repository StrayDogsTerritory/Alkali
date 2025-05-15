#include "engine/Engine.h"
#include "system/MemoryManager.h"
#include "graphics/GraphicsSDL.h"

namespace alk {

	bool cEngine::init()
	{



		mbGameDone = false;
		return true;
	}

	void cEngine::Run()
	{
		while (!IsGameDone())
		{

		}


	}

	bool cEngine::IsGameDone()
	{
		return mbGameDone;
	}
}