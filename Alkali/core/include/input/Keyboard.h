#ifndef ALK_KEYBOARD_H
#define ALK_KEYBOARD_H

#include "system/String.h"

#include "input/InputDevice.h"

#include <vector>

namespace alk {

	enum eKey
	{
		eKey_Q,
		eKey_W,
		eKey_E,
		eKey_R,
		eKey_T,
		eKey_Y,
		eKey_U,
		eKey_I,
		eKey_O,
		eKey_P,
		eKey_A,
		eKey_S,
		eKey_D,
		eKey_F,
		eKey_G,
		eKey_H,
		eKey_J,
		eKey_K,
		eKey_L,
		eKey_Z,
		eKey_X,
		eKey_C,
		eKey_V,
		eKey_B,
		eKey_N,
		eKey_M,

		eKey_Tab,
		eKey_Caps_Lock,
		eKey_Tilde,
		eKey_Comma,
		eKey_Period,
		eKey_Back_Slash,
		eKey_Enter,
		eKey_Forward_Slash,
		eKey_Left_Bracket,
		eKey_Right_Bracket,
		eKey_Semi_Colon,
		eKey_Apostrophe,
		eKey_Equals,
		eKey_Dash,
		eKey_Esc,

		eKey_0,
		eKey_1,
		eKey_2,
		eKey_3,
		eKey_4,
		eKey_5,
		eKey_6,
		eKey_7,
		eKey_8,
		eKey_9,

		eKey_Num_0,
		eKey_Num_1,
		eKey_Num_2,
		eKey_Num_3,
		eKey_Num_4,
		eKey_Num_5,
		eKey_Num_6,
		eKey_Num_7,
		eKey_Num_8,
		eKey_Num_9,

		eKey_F1,
		eKey_F2,
		eKey_F3,
		eKey_F4,
		eKey_F5,
		eKey_F6,
		eKey_F7,
		eKey_F8,
		eKey_F9,
		eKey_F10,
		eKey_F11,
		eKey_F12,

		eKey_LastEnum
	};

	enum eModifier
	{
		eModifier_ALT,
		eModifier_CTRL,
		eModifier_SHFT
	};

	class iKeyboard : public iInputDevice
	{
	public:
		iKeyboard();
		virtual ~iKeyboard();

		virtual bool KeyDown(eKey aKey)=0;

		// is Keyboard active?
		virtual bool KeyboardActive()=0;

	protected:

		unsigned int mlLastActive;

		tString EnumToString(const eKey& aKey);
		eKey StringToEnum(const tString& asString);
		
		std::vector<bool> mvKeyPressed;
	};

}

#endif