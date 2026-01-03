#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H

#include "system/FlagBits.h"
#include "engine/Updateable.h"

#include "system/LogicTimer.h"

namespace alk {

	enum eEngineAPI
	{
		eEngineAPI_eOpenGl,
		eEngineAPI_eLast_Enum
	};

	enum eEngineInit
	{
		eEngineInit_All = FLAGBITZERO,
		eEngineInit_Screen = FLAGBITONE
	};



	class cEngine;
	class cGrpahicsSDL;
	class iEngineSetup;
	class cGraphics;
	class cResources;
	class cLogicTimer;
	class cSystem;
	class cUpdater;
	class cInput;

	extern cEngine* CreateAlkaliEngine(tFlag alEngineSetup, eEngineAPI aeEngineApi);
	extern void DestroyAlkaliEngine(cEngine* apEngine);

	class cEngine
	{
	public:
		cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup);
		~cEngine();

		bool init(tFlag alModuleFlags,iEngineSetup* apGame);

		void Run();


		// Modules
		cSystem* GetSystem() { return mpSystem; }
		cResources* GetResources() { return mpResources; }
		cGraphics* GetGraphics() { return mpGraphics; }
		cInput* GetInput() { return mpInput; }


		// misc
		cUpdater* GetUpdater() { return mpUpdater; }

		static void SetDevicePlugged() { mbDevicePlugged = true; }
		static void SetDeviceUnplugged() { mbDeviceRemoved = true; }

	private:

		bool IsGameDone();
		bool mbGameDone;

		static bool mbDevicePlugged;
		static bool mbDeviceRemoved;

		iEngineSetup* mpGame;

		cSystem* mpSystem;
		cGraphics* mpGraphics;
		cResources* mpResources;
		cInput* mpInput;

		cLogicTimer* mpLogicTimer;
		cUpdater* mpUpdater;
	};


}
#endif
