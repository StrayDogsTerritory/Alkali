#include "input/Input.h"
#include "input/InputEvent.h"
#include "input/InputEventGamepadButton.h"

namespace alk {

	cInputEventGamepadButton::cInputEventGamepadButton(cInput* apInput, eGamepadButton aButton, int alIndex)
	{
		mpInput = apInput;
		mButton = aButton;
		mlIndex = alIndex;
	}

	bool cInputEventGamepadButton::IsTriggered()
	{
		iGamepad* pGamepad = mpInput->GetGamepad(mlIndex);

		if (pGamepad != NULL)
		{
			if (pGamepad->ButtonDown(mButton))
			{
				return true;
			}
		}

		return false;
	}
}