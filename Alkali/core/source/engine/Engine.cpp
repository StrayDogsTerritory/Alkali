#include "system/MemoryManager.h"
#include "engine/Engine.h"

#include "engine/EngineSetupInterface.h"
#include "engine/EngineSDL.h"


namespace alk {


	cEngine* CreateAlkaliEngine()
	{

		alkNew(cSDLEngine, ());

		return alkNew(cEngine, ());
	}


	cEngine::cEngine()
	{
		init();

	}

	bool cEngine::init()
	{

		mbGameDone = false;
		

		mpVideoSDL = mpSetup->CreateVideoModule();


		mpVideoSDL->Init(640, 720, false);


		return true;

	}

	cEngine::~cEngine()
	{
		//alkDelete(mpVideoSDL)
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