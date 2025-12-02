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
#include "system/System.h"

#include "engine/Updater.h"
#include "engine/Updateable.h"
#include "input/Input.h"

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
		alkDelete(mpSystem);
		alkDelete(mpInput);

		// exit the updaters
		alkDelete(mpLogicTimer);
		alkDelete(mpUpdater);

		alkDelete( mpGame );


	}

	bool cEngine::init(tFlag alModuleFlags, iEngineSetup* apGame)
	{
		mpGame = apGame;

		mbGameDone = false;
		
		//create the modules
		Log("Creating System module\n");
		mpSystem = mpGame->CreateSystemModule();

		Log("Creating Graphics module\n");
		mpGraphics = mpGame->CreateGraphicsModule();

		Log("Creating Resource module\n");
		mpResources = alkNew(cResources, ());

		Log("Creating Input module\n");
		mpInput = mpGame->CreateInputModule();

		//init the modules
		mpGraphics->Init(mpResources, 680, 720 , 0);
		mpResources->Init(mpGraphics);


		// create some secondary modules
		mpLogicTimer = alkNew(cLogicTimer, (60));
		mpUpdater = alkNew(cUpdater, ());

		// add engine updates
		mpUpdater->AddEngineModule(mpSystem);
		mpUpdater->AddEngineModule(mpInput);

		return true;
	}

	void cEngine::Run()
	{
		mpGraphics->GetLowGraphics()->SwapBuffer();
		Log("Started cEngine::Run\n");
		SDL_Event lEvent;
		while (!IsGameDone())
		{
		//	Log("Running !IsGameDoneLoop\n");
			while (mpLogicTimer->WantUpdate()) //&& !IsGameDone())
			{
				Log("Running Update Loop\n");
				mpUpdater->RunEngineUpdate(eUpdatableMessageType_OnPreUpdate,0);
				mpUpdater->RunEngineUpdate(eUpdatableMessageType_OnUpdate,0);
				mpUpdater->RunEngineUpdate(eUpdatableMessageType_OnPostUpdate,0);

				if (mpInput->GetIsQuit())
				{
					mbGameDone = true;
				}
			}
			mpLogicTimer->EndLoop();


//			mpGraphics->GetLowGraphics()->SwapBuffer();
		}


	}

	bool cEngine::IsGameDone()
	{
		return  mbGameDone;
	}
	
}