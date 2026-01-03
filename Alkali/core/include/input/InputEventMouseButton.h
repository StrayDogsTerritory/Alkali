#ifndef ALK_INPUTEVENTMOUSEBUTTON_H
#define ALK_INPUTEVENTMOUSEBUTTON_H

#include "input/InputEvent.h"
#include "input/Mouse.h"

namespace alk {

	class cInputEventMouseButton : public iInputEvent
	{
	public:
		cInputEventMouseButton(cInput* apInput, eMouseButton aMouseButton);
		~cInputEventMouseButton();

		bool IsTriggered();

	private:
		eMouseButton mMouseButton;
		cInput* mpInput;
	};
}

#endif
