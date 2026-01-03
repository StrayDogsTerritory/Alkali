#include "input/Action.h"
#include "input/InputEvent.h"
#include "input/InputEventKeyboard.h"
#include "input/InputEventMouseButton.h"
#include "input/InputEventGamepadButton.h"

#include "system/SystemTypes.h"

namespace alk {

	cAction::cAction(tString asName, int alID, cInput* apInput)
	{
		mlID = alID;
		msName = asName;

		mpInput = apInput;

		mbBecameTriggered = false;
		mbIsDown = false;
	}

	cAction::~cAction()
	{
		DeleteAll(mvInputEvent);
	}

	void cAction::AddControllerButton(eGamepadButton aButton, int alIndex)
	{
		AddInputEvent(alkNew(cInputEventGamepadButton, (mpInput, aButton, alIndex)));
	}

	void cAction::AddMouseButton(eMouseButton aMouseButton)
	{
		AddInputEvent(alkNew(cInputEventMouseButton, (mpInput, aMouseButton)));
	}

	void cAction::AddKey(eKey aKey)
	{
		AddInputEvent(alkNew(cInputEventKeyboard, (mpInput, aKey)));
	}

	void cAction::AddInputEvent(iInputEvent* apInputEvent)
	{
		mvInputEvent.push_back(apInputEvent);
	}

	bool cAction::IsTriggered()
	{
		return mbIsDown;
	}

	bool cAction::BecameTriggered()
	{
		if (!mbBecameTriggered && mbIsDown)
		{
			mbBecameTriggered = true;
			return true;
		}

		return false;
	}

	void cAction::Update(float afStep)
	{
		mbIsDown = false;
		for (int i = 0; i < mvInputEvent.size(); ++i)
		{
			if (mvInputEvent[i]->IsTriggered())
			{
				mbIsDown = true;
			}
		}
		if (mbIsDown)
		{
			
		}
		else
		{
			mbBecameTriggered = false;
		}

	}

}