#ifndef ALK_MOUSE_H
#define ALK_MOUSE_H

#include "input/InputDevice.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace alk {

	enum eMouseButton
	{
		eMouseButton_Left,
		eMouseButton_Right,
		eMouseButton_Middle,

		eMouseButton_4,
		eMouseButton_5,

		eMouseButton_LastEnum
	};

	enum eScrollWheel
	{
		eScrollWheel_Down,
		eScrollWheel_Up,

		eScrollWheel_LastEnum
	};

	class iMouse : public iInputDevice
	{
	public:
		iMouse() {}
		virtual ~iMouse() {}

		virtual tVector2l GetMousePos()=0;
		virtual bool ButtonDown(eMouseButton aKey) = 0;

		// is Mouse active?
		virtual bool MouseActive() = 0;

		tString ButtonToString(eMouseButton aButton)
		{
			switch (aButton)
			{
			case eMouseButton_Left: return "Left Click";
			case eMouseButton_Middle: return "Middle Click";
			case eMouseButton_Right: return "Right Click";

			case eMouseButton_4: return "Mouse 4";
			case eMouseButton_5: return "Mouse 5";

			default:
				return "NULL";
			}
		}
	protected:
		std::vector<bool> mvMouseButtonArray;
		tVector2l mvMousePos;

	};
}

#endif
