#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H

#include "system/FlagBits.h"


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
	class cVideoSDL;
	class iEngineSetup;
	class cVideo;
	class cGraphics;
	class cResources;

	extern cEngine* CreateAlkaliEngine(tFlag alEngineSetup, eEngineAPI aeEngineApi);
	extern void DestroyAlkaliEngine(cEngine* apEngine);

	class cEngine
	{
	public:
		cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup);
		~cEngine();

		bool init(tFlag alModuleFlags,iEngineSetup* apGame);

		void Run();

	private:

		bool IsGameDone();
		bool mbGameDone;

		iEngineSetup* mpGame;


		cVideo* mpVideo;
		cGraphics* mpGraphics;
		cResources* mpResources;
	};


}
#endif
