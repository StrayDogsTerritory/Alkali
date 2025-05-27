#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H

#include "EngineSetupInterface.h"
#include "video/VideoSDL.h"


class iEngineSetup;
class cVideoSDL;


namespace alk {

	class cEngine;


	extern cEngine* CreateAlkaliEngine();
	extern void DestroyAlkaliEngine(cEngine* apEngineInstance);

	class cEngine
	{
	public:
		cEngine();
		~cEngine();

		bool init();

		void Run();

	private:

		bool IsGameDone();
		bool mbGameDone;

		iEngineSetup* mpSetup;


		cVideoSDL* mpVideoSDL;
	};


}
#endif
