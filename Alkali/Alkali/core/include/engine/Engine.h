#ifndef ALK_ENGINE_H
#define ALK_ENGINE_H

namespace alk {
	class cEngine
	{
	public:
		bool init();

		void Run();

	private:

		bool IsGameDone();


		bool mbGameDone;
	};


}
#endif
