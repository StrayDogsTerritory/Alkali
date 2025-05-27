#include "system/MemoryManager.h"
#include "engine/Engine.h"
#include "engine/EngineSDL.h"
#include "engine/EngineSetupInterface.h"
#include "video/VideoSDL.h"

namespace alk {


	cEngine* CreateAlkaliEngine()
	{
		iEngineSetup* pGameSetup = NULL;

		pGameSetup = alkNew(cSDLEngine, ());

		

		return alkNew(cEngine, (pGameSetup));
	}

	void DestroyAlkaliEngine(cEngine* apEngine)
	{
		alkDelete( apEngine );


		
	}



	cEngine::cEngine(iEngineSetup* apGameSetup)
	{
		//mpGame = apGameSetup;

		init(apGameSetup);
	}

	cEngine::~cEngine()
	{
	}

	bool cEngine::init(iEngineSetup* apGame)
	{
		mpGame = apGame;


		mbGameDone = false;
		return true;

		mpVideoSDL = mpGame->CreateVideoModule();
		mpVideoSDL->Init(600, 800, false);


	}

	void cEngine::Run()
	{
		while (!IsGameDone())
		{
			/*if (mpVideoSDL->mbWorked)
				mbGameDone = true;*/
		}


	}

	bool cEngine::IsGameDone()
	{
		bool bDone = mbGameDone;

		return bDone;
	}
	
}