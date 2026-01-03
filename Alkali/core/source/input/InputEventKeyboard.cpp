#include "input/InputEventKeyboard.h"

namespace alk {

	cInputEventKeyboard::cInputEventKeyboard(cInput* apInput, eKey aKey)
	{
		mpInput = apInput;
		mKey = aKey;
	}

	cInputEventKeyboard::~cInputEventKeyboard()
	{

	}

	bool cInputEventKeyboard::IsTriggered()
	{
		iKeyboard* pBoard = mpInput->GetKeyboard();
		if (pBoard->KeyDown(mKey))
		{
			return true;
		}

		return false;
	}
}