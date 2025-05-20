#include "system/MemoryManager.h"
#include "engine/Engine.h"

namespace alk {


	cEngine* CreateAlkaliEngine()
	{

	//	alkNew();

		return alkNew(cEngine, ());
	}



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
		bool bDone = mbGameDone;

		return bDone;
	}
	
}