#ifndef ALK_MOUSE_H
#define ALK_MOUSE_H

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

	class iMouse
	{
	};
}

#endif
