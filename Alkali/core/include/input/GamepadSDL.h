#ifndef ALK_GAMEPADSDL_H
#define ALK_GAMEPADSDL_H

#include "input/InputSDL.h"
#include "input/Gamepad.h"

#include <SDL3/SDL.h>

namespace alk {

	class cGamepadSDL : public iGamepad
	{
	public:
		cGamepadSDL(cInputSDL* mpInputSDL, int alID, int alIndex);
		~cGamepadSDL();

		void Update();

		bool ButtonDown(eGamepadButton aKey);

		bool ControllerActive();

		void RumbleController(int alLeftRumble, int alRightRumble, int alDuration);
		void ChangeLEDColour(cColour aCol);

		tString GetName() { return msName; }
		int GetIndex() { return mlIndex; }
	private:
		eGamepadButton SDLToButton(int alKey);

		cInputSDL* mpInputSDL;
		SDL_Gamepad* mpHandle;
	};

}

#endif