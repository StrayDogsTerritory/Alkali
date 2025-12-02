#ifndef ALK_KEYBOARDSDL_H
#define ALK_KEYBOARDSDL_H

#include "input/Keyboard.h"
#include "input/InputSDL.h"

#include <SDL3/SDL.h>

namespace alk {

	class cKeyboardSDL : public iKeyboard
	{
	public:
		cKeyboardSDL(cInputSDL* apInput);

		void Update();

		eKey SDLCodeToKey(int alKey);

	private:
		cInputSDL* mpInputSDL;
		void ResetKeysPressed();
	};

}

#endif
