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
		alkDelete( mpVideo );

		alkDelete( mpGame );


	}

	bool cEngine::init(iEngineSetup* apGame)
	{
		mpGame = apGame;


		mbGameDone = false;
		return true;

		mpVideo = mpGame->CreateVideoModule();
		mpVideo->Init(640, 720, 0);


	}

	void cEngine::Run()
	{
		while (!IsGameDone())
		{
			/*if (mpVideoSDL->mbWorked)
				mbGameDone = true;*/

			for (int i; i < 25000; ++i)
			{
				if (i == 25000)
					mbGameDone = true;
			}
		}


	}

	bool cEngine::IsGameDone()
	{
		bool bDone = mbGameDone;

		return bDone;
	}
	
}