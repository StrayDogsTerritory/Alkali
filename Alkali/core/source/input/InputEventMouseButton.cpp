#include "input/InputEventMouseButton.h"
#include "input/Mouse.h"

namespace alk {

	cInputEventMouseButton::cInputEventMouseButton(cInput* apInput, eMouseButton aMouseButton)
	{
		mpInput = apInput;
		mMouseButton = aMouseButton;
	}


	cInputEventMouseButton::~cInputEventMouseButton()
	{

	}

	bool cInputEventMouseButton::IsTriggered()
	{
		iMouse* pMouse = mpInput->GetMouse();

		if (pMouse->ButtonDown(mMouseButton))
		{
			return true;
		}

		return false;
	}
}