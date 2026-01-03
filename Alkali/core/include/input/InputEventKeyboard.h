#ifndef ALK_INPUTEVENTKEYBOARD_H
#define ALK_INPUTEVENTKEYBOARD_H

#include "input/InputEvent.h"

namespace alk {

	class cInputEventKeyboard : public iInputEvent
	{
	public:
		cInputEventKeyboard(cInput* apInput, eKey aKey);
		~cInputEventKeyboard();

		bool IsTriggered();

	private:
		eKey mKey;
		cInput* mpInput;
	};

}

#endif
