#include "system/MemoryManager.h"
#include "engine/Engine.h"
#include "engine/EngineSDL.h"
#include "engine/EngineSetupInterface.h"
#include "video/VideoSDL.h"
#include "video/Video.h"
#include "engine/LogWriter.h"

#include "graphics/Graphics.h"

#include "math/Math.h"
// temp 
#include "SDL3/SDL.h"

namespace alk {


	cEngine* CreateAlkaliEngine(tFlag alEngineSetup, eEngineAPI aeEngineApi)
	{
		iEngineSetup* pGameSetup = NULL;

		switch (aeEngineApi)
		{
		case eEngineAPI_eOpenGl:
			 pGameSetup = alkNew(cSDLEngine, ());
		}
		return alkNew(cEngine, (alEngineSetup, pGameSetup));
	}

	void DestroyAlkaliEngine(cEngine* apEngine)
	{

		alkDelete( apEngine );
		
	}



	cEngine::cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup )
	{
		init(alEngineSetup, apGameSetup);
	}

	cEngine::~cEngine()
	{
		alkDelete( mpVideo );
		alkDelete( mpGraphics );


		alkDelete( mpGame );


	}

	bool cEngine::init(tFlag alModuleFlags, iEngineSetup* apGame)
	{
		mpGame = apGame;


		mbGameDone = false;
		
		//create the modules
		Log("Creating graphics module\n");
		mpGraphics = alkNew(cGraphics, ( alModuleFlags));

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