#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H


class cVideoSDL;


namespace alk {

	class cEngine;


	extern cEngine* CreateAlkaliEngine();

	class cEngine
	{
	public:
		bool init();

		void Run();

	private:

		bool IsGameDone();
		bool mbGameDone;




		cVideoSDL* mpVideoSDL;
	};


}
#endif
