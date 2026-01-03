#ifndef ALK_ACTION_H
#define ALK_ACTION_H

#include "system/String.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "input/Gamepad.h"

#include <vector>
namespace alk {

	class iInputEvent;
	class cInput;

	class cAction
	{
	public: 
		cAction(tString asName, int alID, cInput* apInput);
		~cAction();

		void AddControllerButton(eGamepadButton aButton, int alIndex);

		void AddMouseButton(eMouseButton aMouseButton);
		void AddKey(eKey aKey);

		void AddInputEvent(iInputEvent* apInputEvent);

		bool IsTriggered();

		bool BecameTriggered();

		void Update(float afStep);

		tString GetName() { return msName; }
		int GetID() { return mlID; }


		iInputEvent* GetInputEvent(int aEvent)
		{
			return mvInputEvent[aEvent];
		}

	private:
		tString msName;
		int mlID;
		cInput* mpInput;

		bool mbIsDown;
		bool mbBecameTriggered;

		std::vector<iInputEvent*> mvInputEvent;
	};
}


#endif
