#ifndef ALK_INPUTEVENTGAMEPADBUTTON_H
#define ALK_INPUTEVENTGAMEPADBUTTON_H

#include "input/InputEvent.h"
#include "input/Gamepad.h"

namespace alk {

	class cInputEventGamepadButton : public iInputEvent
	{
	public:
		cInputEventGamepadButton(cInput* apInput, eGamepadButton aButton, int alIndex);
		~cInputEventGamepadButton() {}
		

		bool IsTriggered();

	private:
		cInput* mpInput;
		eGamepadButton mButton;
		int mlIndex;
	};

}

#endif
