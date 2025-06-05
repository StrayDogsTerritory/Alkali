#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H




namespace alk {

	class cEngine;
	class cVideoSDL;
	class iEngineSetup;
	class cVideo;
	class cGraphics;


	extern cEngine* CreateAlkaliEngine();
	extern void DestroyAlkaliEngine(cEngine* apEngine);

	class cEngine
	{
	public:
		cEngine(iEngineSetup* apGameSetup);
		~cEngine();

		bool init(iEngineSetup* apGame);

		void Run();

	private:

		bool IsGameDone();
		bool mbGameDone;

		iEngineSetup* mpGame;


		cVideo* mpVideo;
		cGraphics* mpGraphics;
	};


}
#endif
