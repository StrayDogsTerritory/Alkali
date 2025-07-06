#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H

#include "system/FlagBits.h"


namespace alk {

	enum eGraphicsAPI
	{
		eEngineAPI_eOpenGl,
		eEngineAPI_eDirectX11,
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


	extern cEngine* CreateAlkaliEngine(tFlag alEngineSetup, eGraphicsAPI aeGraphicsApi);
	extern void DestroyAlkaliEngine(cEngine* apEngine);

	class cEngine
	{
	public:
		cEngine(tFlag alEngineSetup, iEngineSetup* apGameSetup, eGraphicsAPI aeGraphicsApi);
		~cEngine();

		bool init(tFlag alModuleFlags,iEngineSetup* apGame);

		void Run();

	private:

		bool IsGameDone();
		bool mbGameDone;

		eGraphicsAPI meGraphicsApi;
		eGraphicsAPI GetGraphicsApi() { return meGraphicsApi; }

		iEngineSetup* mpGame;


		cVideo* mpVideo;
		cGraphics* mpGraphics;
	};


}
#endif
