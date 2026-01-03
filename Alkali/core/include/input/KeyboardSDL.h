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
		~cKeyboardSDL() {}

		void Update();

		bool KeyDown(eKey aKey);

		bool KeyboardActive();

	private:
		eKey SDLCodeToKey(int alKey);
		void ResetKeysPressed();

		cInputSDL* mpInputSDL;
	};

}

#endif
