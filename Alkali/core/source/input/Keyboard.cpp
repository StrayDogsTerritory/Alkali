#include "input/Keyboard.h"
#include "system/String.h"


namespace alk {

	iKeyboard::iKeyboard()
	{

	}

	iKeyboard::~iKeyboard()
	{
	}

	tString iKeyboard::EnumToString(const eKey& aKey)
	{
		switch (aKey)
		{
		case eKey_Q: return "Q";
		case eKey_W: return "W";
		case eKey_E: return "E";
		case eKey_R: return "R";
		case eKey_T: return "T";
		case eKey_Y: return "Y";
		case eKey_U: return "U";
		case eKey_I: return "I";
		case eKey_O: return "O";
		case eKey_P: return "P";
		case eKey_A: return "A";
		case eKey_S: return "S";
		case eKey_D: return "D";
		case eKey_F: return "F";
		case eKey_G: return "G";
		case eKey_H: return "H";
		case eKey_J: return "J";
		case eKey_K: return "K";
		case eKey_L: return "L";
		case eKey_Z: return "Z";
		case eKey_X: return "X";
		case eKey_C: return "C";
		case eKey_V: return "V";
		case eKey_B: return "B";
		case eKey_N: return "N";
		case eKey_M: return "M";

		case eKey_Tab: return "Tab";
		case eKey_Caps_Lock: return "Caps_Lock";
		case eKey_Tilde: return "Tilde";
		case eKey_Comma: return "Comma";
		case eKey_Period: return "Period";
		case eKey_Back_Slash: return "Back_Slash";
		case eKey_Enter: return "Enter";
		case eKey_Forward_Slash: return "Forward_Slash";
		case eKey_Left_Bracket: return "Left_Bracket";
		case eKey_Right_Bracket: return "Right_Bracket";
		case eKey_Semi_Colon : return "Semi_Colon";
		case eKey_Apostrophe: return "Apostrophe";
		case eKey_Equals: return "Equals";
		case eKey_Dash: return "Dash";
		case eKey_Esc: return "Escape";

		case eKey_0: return "0";
		case eKey_1: return "1";
		case eKey_2: return "2";
		case eKey_3: return "3";
		case eKey_4: return "4";
		case eKey_5: return "5";
		case eKey_6: return "6";
		case eKey_7: return "7";
		case eKey_8: return "8";
		case eKey_9: return "9";

		case eKey_Num_0: return "0";
		case eKey_Num_1: return "1";
		case eKey_Num_2: return "2";
		case eKey_Num_3: return "3";
		case eKey_Num_4: return "4";
		case eKey_Num_5: return "5";
		case eKey_Num_6: return "6";
		case eKey_Num_7: return "7";
		case eKey_Num_8: return "8";
		case eKey_Num_9: return "9";

		case eKey_F1: return "F1";
		case eKey_F2: return "F2";
		case eKey_F3: return "F3";
		case eKey_F4: return "F4";
		case eKey_F5: return "F5";
		case eKey_F6: return "F6";
		case eKey_F7: return "F7";
		case eKey_F8: return "F8";
		case eKey_F9: return "F9";
		case eKey_F10: return "F10";
		case eKey_F11: return "F11";
		case eKey_F12: return "F12";

		default:
			return "INVALID";
		}
	}

	eKey iKeyboard::StringToEnum(const tString& asString)
	{
		//if ( ) return ;


		return eKey_LastEnum;
	}
}