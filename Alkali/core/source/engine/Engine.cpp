#include "system/MemoryManager.h"
#include "engine/Engine.h"
#include "engine/EngineSDL.h"
#include "engine/EngineSetupInterface.h"
#include "graphics/GraphicsSDL.h"
#include "graphics/Graphics.h"
#include "engine/LogWriter.h"

#include "math/Math.h"
// temp 
#include "SDL3/SDL.h"

#include "resources/Resources.h"
#include "system/LogicTimer.h"

namespace alk {


	cEngine* CreateAlkaliEngine(tFlag alEngineSetup, eEngineAPI aeEngineApi)
	{
		iEngineSetup* pGameSetup = NULL;

		switch (aeEngineApi)
		{
		case eEngineAPI_eOpenGl:
			 pGameSetup = alkNew(cSDLEngine, (alEngineSetup));
		}
		return alkNew(cEngine, (alEngineSetup, pGameSetup));
	}

	void DestroyAlkaliEngine(cEngine* apEngine)
	{
		Log("Destroying Engine\n");
		alkDelete( apEngine );
	}



	cEngine::cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup )
	{
		init(alEngineSetup, apGameSetup);
	}

	cEngine::~cEngine()
	{
		Log("cEngine Destructor\n");
		alkDelete(mpGraphics);
		alkDelete(mpResources);
		


		alkDelete( mpGame );


	}

	bool cEngine::init(tFlag alModuleFlags, iEngineSetup* apGame)
	{
		mpGame = apGame;


		mbGameDone = false;
		
		//create the modules

		Log("Creating Graphics module\n");
		mpGraphics = mpGame->CreateGraphicsModule();

		Log("Creating Resource module\n");
		mpResources = alkNew(cResources, ());


		//init the modules

		mpGraphics->Init(mpResources, 680, 720 , 0);
		mpResources->Init(mpGraphics);

		return true;
	}

	void cEngine::Run()
	{
		SDL_Event mSDLEvent;

		while (!IsGameDone())
		{
			//Log("Loop Running\n");
			//this is all temporary, do this in an actual input module
			while(SDL_PollEvent(&mSDLEvent))
			{
			//	Log("Polling Events\n");
				if (mSDLEvent.type == SDL_EVENT_QUIT)
				{
					Log("Quitting\n");
					mbGameDone = true;
				}
			

			}

		//	mpGraphics->GetLowGraphics()->SwapBuffer();
			
		}


	}

	bool cEngine::IsGameDone()
	{
		return  mbGameDone;
	}
	
}