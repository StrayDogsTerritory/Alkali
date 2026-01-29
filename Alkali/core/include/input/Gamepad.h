#ifndef ALK_GAMEPAD_H
#define ALK_GAMEPAD_H

#include "system/System.h"

#include "input/InputDevice.h"

#include "graphics/Colour.h"

#include <vector>


enum eGamepadButton
{
	///////////////////
	// Common Buttons
	eGamepadButton_0, // X on PS or A on XBox
	eGamepadButton_1, // O on PS or B on XBox
	eGamepadButton_2, // Square or X
	eGamepadButton_3, // Triangle or Y

	eGamepadButton_Left_Trigger, // L1
	eGamepadButton_Right_Trigger, // R2

	eGamepadButton_Left_Bumber, // L2
	eGamepadButton_Right_Bumber, // R2

	eGamepadButton_Left_Stick, // L3
	eGamepadButton_Right_Stick, // R3

	eGamepadButton_Touchpad, // touchpad on PS controllers

	// special buttons... hard to name for nintendo controllers
	eGamepadButton_Options,
	eGamepadButton_Social,
	eGamepadButton_Special_3, // nintendo - button or PS middle thing, not a thing for XBox controllers... arrgh why couldn't they standardize this shit!!!!

	// hat or what ever its called
	eGamepadButton_Hat_Up,
	eGamepadButton_Hat_Down,
	eGamepadButton_Hat_Left,
	eGamepadButton_Hat_Right,

	eGamepadButton_LastEnum
};


namespace alk {

	class iGamepad : public iInputDevice
	{
	public:
		iGamepad(int alID,int alIndex) { mlIndex = alIndex; }
		virtual ~iGamepad() {}

		virtual bool ButtonDown(eGamepadButton aButton) = 0;

		// is Keyboard active?
		virtual bool ControllerActive() = 0;

		virtual void RumbleController(int alLeftRumble, int alRightRumble, int alDuration) = 0;
		virtual void ChangeLEDColour(cColour aCol)=0;

		virtual tString GetName()=0;
		virtual int GetIndex()=0;

		tString EnumToString(eGamepadButton aButton)
		{
			switch (aButton)
			{
			case eGamepadButton_0: return "Button South";
			case eGamepadButton_1: return "Button East";
			case eGamepadButton_2: return "Button West";
			case eGamepadButton_3: return "Button North";
			}
		}

	protected:
		std::vector<bool> mvGamepadButtonArray;
		int mlIndex;

		tString msName;
	};
}

#endif
