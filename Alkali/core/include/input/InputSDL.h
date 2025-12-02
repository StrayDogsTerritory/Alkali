#ifndef ALK_INPUTSDL_H
#define ALK_INPUTSDL_H

#include "input/InputInterface.h"

#include <SDL3/SDL.h>

#include <list>
namespace alk {
	class iInputDevice;
	class iMouse;
	class iKeyboard;
	class iGamepad;

	typedef std::list<SDL_Event> tEventList;
	typedef tEventList::iterator tEventListit;

	class cInputSDL : public iInput
	{
	public:
		cInputSDL();
		~cInputSDL();

		void Update(float afTimeStep);
		bool GetIsQuit();

		iKeyboard* CreateKeyboard();
		iMouse* CreateMouse();
		iGamepad* CreateGamepad();

		tEventList mLstSDLEvents;
	private:
		bool mbQuitting;
	};

}

#endif