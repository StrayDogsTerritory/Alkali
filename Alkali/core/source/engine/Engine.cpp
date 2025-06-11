#include "system/MemoryManager.h"
#include "engine/Engine.h"
#include "engine/EngineSDL.h"
#include "engine/EngineSetupInterface.h"
#include "video/VideoSDL.h"
#include "video/Video.h"
#include "engine/LogWriter.h"

#include "graphics/Graphics.h"

// temp 
#include "SDL3/SDL.h"

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

		init(apGameSetup);
	}

	cEngine::~cEngine()
	{
		alkDelete( mpVideo );
		alkDelete( mpGraphics );


		alkDelete( mpGame );


	}

	bool cEngine::init(iEngineSetup* apGame)
	{
		mpGame = apGame;


		mbGameDone = false;
		
		//create the modules
		Log("Creating graphics module\n");
		mpGraphics = alkNew(cGraphics, ());

		Log("Creating Video module\n");
		mpVideo = mpGame->CreateVideoModule();
		


		//init the modules

		mpVideo->Init( 680, 720 , 0);

		return true;
	}

	void cEngine::Run()
	{
		SDL_Event mSDLEvent;

		while (!IsGameDone())
		{

			//this is all temporary, do this in an actual input module
			while(SDL_PollEvent(&mSDLEvent))
			{
				if (mSDLEvent.type == SDL_EVENT_QUIT)
				{
					mbGameDone = true;
				}
			

			}
			
			
			
		}


	}

	bool cEngine::IsGameDone()
	{
		return  mbGameDone;
	}
	
}