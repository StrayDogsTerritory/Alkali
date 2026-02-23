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
#include "system/SystemInterface.h"
#include "system/SystemTypes.h"

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
		alkDelete( apEngine );
	}

	bool cEngine::mbDevicePlugged = false;
	bool cEngine::mbDeviceRemoved = false;

	cEngine::cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup )
	{
		init(alEngineSetup, apGameSetup);
	}

	cEngine::~cEngine()
	{
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
		
		// @TODO: REPLACE EVERY HARDCODED VALUE WITH INIT VARS CLASS!!!!!!!!!!!!!!!!!!
		Log("Creating Engine modules\n");
		Log("---------------------------------------------\n");
		//create the modules
		Log("Creating System module\n");
		mpSystem = mpGame->CreateSystemModule();

		Log("Creating Graphics module\n");
		mpGraphics = mpGame->CreateGraphicsModule();

		Log("Creating Resource module\n");
		mpResources = mpGame->CreateResourcesModule();

		Log("Creating Input module\n");
		mpInput = mpGame->CreateInputModule();
		mpInput->SetInputFrozen(true);
		Log("---------------------------------------------\n\n");
		//init the modules
		Log("Initialize Engine Modules\n");
		Log("---------------------------------------------\n");

		Log("Initializing System module\n");
		mpSystem->Init();

		Log("Initializing Resource module\n");
		mpResources->Init(mpGraphics);

		Log("Initializing Graphics module\n");
		mpGraphics->Init(mpResources, 1080, 1920 , 0);
		
		Log("Initializing Input module\n");
		mpInput->Init();

		// create some secondary modules
		mpLogicTimer = alkNew(cLogicTimer, (60));
		mpUpdater = alkNew(cUpdater, ());

		// add engine updates
		mpUpdater->AddEngineModule(mpSystem);
		mpUpdater->AddEngineModule(mpResources);
		mpUpdater->AddEngineModule(mpInput);
		mpUpdater->AddEngineModule(mpGraphics);
		
		return true;
	}

	void cEngine::Run()
	{
		
		Log("-----------------------------------\n\n");

		mpInput->SetInputFrozen(false);
		
		while (!IsGameDone())
		{
		//	Log("Running !IsGameDoneLoop\n");
			while (mpLogicTimer->WantUpdate()) //&& !IsGameDone())
			{
				
				mpUpdater->RunEngineUpdate(eUpdateableMessageType_OnPreUpdate,mpLogicTimer->GetUpdateStep());
		

		
				mpUpdater->RunEngineUpdate(eUpdateableMessageType_OnUpdate, mpLogicTimer->GetUpdateStep());
			
		
				mpUpdater->RunEngineUpdate(eUpdateableMessageType_OnPostUpdate, mpLogicTimer->GetUpdateStep());
			

				if (mbDevicePlugged)
				{
					mbDevicePlugged = false;
					mpUpdater->RunEngineUpdate(eUpdateableMessageType_DeviceAdded,0);
				}
				if (mbDeviceRemoved)
				{
					mbDeviceRemoved = false;
					mpUpdater->RunEngineUpdate(eUpdateableMessageType_DeviceRemoved, 0);
				}

				if (mpInput->GetIsQuit())
				{
					mbGameDone = true;
				}
			}
			mpLogicTimer->EndLoop();

			mpGraphics->GetLowGraphics()->SwapBuffer();

			mpGraphics->GetLowGraphics()->ClearFrameBuffer(1);

			mpGraphics->DrawTemp();

			mpGraphics->GetLowGraphics()->FlushRender();
		}
	}

	bool cEngine::IsGameDone()
	{
		return  mbGameDone;
	}
	
}