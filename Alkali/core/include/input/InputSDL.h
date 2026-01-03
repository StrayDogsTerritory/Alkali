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

	class iGraphics;

	class cInputSDL : public iInput
	{
	public:
		cInputSDL(iGraphics* apGraphics);
		~cInputSDL();

		void Update(float afTimeStep);
		bool GetIsQuit();
		void SetRelativeMouse(bool abX);

		int GetNumberOfGamepads();

		int GetGamepadID();

		iKeyboard* CreateKeyboard();
		iMouse* CreateMouse();
		iGamepad* CreateGamepad(int alID, int alIndex);

		tEventList mLstSDLEvents;
	private:
		// test
		unsigned int mlGamepadJoyID;

		iGraphics* mpGraphics;
		bool mbQuitting;
	};

}

#endif