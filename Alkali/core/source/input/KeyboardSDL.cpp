#include "input/KeyboardSDL.h"

#include "engine/LogWriter.h"

namespace alk {

	cKeyboardSDL::cKeyboardSDL(cInputSDL* apInputSDL)
	{
		mpInputSDL = apInputSDL;
		mvKeyPressed.resize(eKey_LastEnum); //fix crashes related from buffer overflowing

		ResetKeysPressed();
	}

	void cKeyboardSDL::Update()
	{
		std::list<SDL_Event>::iterator it = mpInputSDL->mLstSDLEvents.begin();
		for (; it != mpInputSDL->mLstSDLEvents.end(); it++)
		{
			SDL_Event* pEvent = &(*it);
			if (pEvent->type == SDL_EVENT_KEY_DOWN || pEvent->type == SDL_EVENT_KEY_UP)
			{
				eKey Key = SDLCodeToKey(pEvent->key.key);
				mvKeyPressed[Key] = pEvent->key.down ? true : false;
			}
		}
	}

	void cKeyboardSDL::ResetKeysPressed()
	{
		mvKeyPressed.assign(mvKeyPressed.size(), false);
	}

	
	bool cKeyboardSDL::KeyDown(eKey aKey)
	{
		return mvKeyPressed[aKey] == true;
	}
	
	bool cKeyboardSDL::KeyboardActive()
	{
		for (int i = 0; i < eKey_LastEnum; ++i)
		{
			if (mvKeyPressed[(eKey)i] == true)
			{
				return true;
			}
		}
		return false;
	}

	eKey cKeyboardSDL::SDLCodeToKey(int alKey)
	{
		switch (alKey)
		{
		case SDLK_A: return eKey_A;
		case SDLK_B: return eKey_B;
		case SDLK_C: return eKey_C;
		case SDLK_D: return eKey_D;
		case SDLK_E: return eKey_E;
		case SDLK_F: return eKey_F;
		case SDLK_G: return eKey_G;
		case SDLK_H: return eKey_H;
		case SDLK_I: return eKey_I;
		case SDLK_J: return eKey_J;
		case SDLK_K: return eKey_K;
		case SDLK_L: return eKey_L;
		case SDLK_M: return eKey_M;
		case SDLK_N: return eKey_N;
		case SDLK_O: return eKey_O;
		case SDLK_P: return eKey_P;
		case SDLK_Q: return eKey_Q;
		case SDLK_R: return eKey_R;
		case SDLK_S: return eKey_S;
		case SDLK_T: return eKey_T;
		case SDLK_U: return eKey_U;
		case SDLK_V: return eKey_V;
		case SDLK_W: return eKey_W;
		case SDLK_X: return eKey_X;
		case SDLK_Y: return eKey_Y;
		case SDLK_Z: return eKey_Z;
		case SDLK_SPACE: return eKey_Space;

		case SDLK_ESCAPE: return eKey_Esc;
		case SDLK_CAPSLOCK: return eKey_Caps_Lock;
		case SDLK_TAB: return eKey_Tab;
		case SDLK_BACKSPACE: return eKey_Backspace;
		case SDLK_RETURN: return eKey_Enter;
		case SDLK_LALT: return eKey_LAlt;
		case SDLK_RALT: return eKey_RAlt;
		case SDLK_LCTRL: return eKey_LCtrl;
		case SDLK_RCTRL: return eKey_RCtrl;
		case SDLK_LSHIFT: return eKey_LShift;
		case SDLK_RSHIFT: return eKey_RShift;
		case SDLK_APPLICATION: return eKey_Menu;
		case SDLK_LGUI: return eKey_GUI;
		case SDLK_RGUI: return eKey_GUI;
		case SDLK_PLUS: return eKey_Plus;
		case SDLK_EQUALS: return eKey_Equals;
		case SDLK_UNDERSCORE: return eKey_Underscore;
		case SDLK_MINUS: return eKey_Dash;
		case SDLK_TILDE: return eKey_Tilde;
		case SDLK_GRAVE: return eKey_Backtick;
		case SDLK_LEFTBRACE: return eKey_Left_Brace;
		case SDLK_RIGHTBRACE: return eKey_Right_Brace;
		case SDLK_LEFTBRACKET: return eKey_Left_Bracket;
		case SDLK_RIGHTBRACKET: return eKey_Right_Bracket;
		case SDLK_BACKSLASH: return eKey_Back_Slash;
		case SDLK_PIPE: return eKey_Pipe;
		case SDLK_SEMICOLON: return eKey_Semi_Colon;
		case SDLK_COLON: return eKey_Colon;
		case SDLK_APOSTROPHE: return eKey_Apostrophe;
		case SDLK_DBLAPOSTROPHE: return eKey_Quotation;
		case SDLK_SLASH: return eKey_Forward_Slash;
		case SDLK_QUESTION: return eKey_Question;
		case SDLK_PERIOD: return eKey_Period;
		case SDLK_LESS: return eKey_Less;
		case SDLK_COMMA: return eKey_Comma;
		case SDLK_GREATER: return eKey_Greater;

		case SDLK_EXCLAIM: return eKey_Exclamation;
		case SDLK_AT: return eKey_At;
		case SDLK_HASH: return eKey_Pound;
		case SDLK_DOLLAR: return eKey_Dollar;
		case SDLK_PERCENT: return eKey_Percent;
		case SDLK_CARET: return eKey_Caret;
		case SDLK_AMPERSAND: return eKey_Ampersand;
		case SDLK_ASTERISK: return eKey_Asterisk;
		case SDLK_LEFTPAREN: return eKey_Left_Parenthesese;
		case SDLK_RIGHTPAREN: return eKey_Right_Parenthesese;

		case SDLK_F1: return eKey_F1;
		case SDLK_F2: return eKey_F2;
		case SDLK_F3: return eKey_F3;
		case SDLK_F4: return eKey_F4;
		case SDLK_F5: return eKey_F5;
		case SDLK_F6: return eKey_F6;
		case SDLK_F7: return eKey_F7;
		case SDLK_F8: return eKey_F8;
		case SDLK_F9: return eKey_F9;
		case SDLK_F10: return eKey_F10;
		case SDLK_F11: return eKey_F11;
		case SDLK_F12: return eKey_F12;
			
		case SDLK_0: return eKey_0;
		case SDLK_1: return eKey_1;
		case SDLK_2: return eKey_2;
		case SDLK_3: return eKey_3;
		case SDLK_4: return eKey_4;
		case SDLK_5: return eKey_5;
		case SDLK_6: return eKey_6;
		case SDLK_7: return eKey_7;
		case SDLK_8: return eKey_8;
		case SDLK_9: return eKey_9;

		case SDLK_UP: return eKey_Up;
		case SDLK_DOWN: return eKey_Down;
		case SDLK_LEFT: return eKey_Left;
		case SDLK_RIGHT: return eKey_Right;

		case SDLK_PRINTSCREEN: return eKey_Print_Screen;
		case SDLK_SCROLLLOCK: return eKey_Scroll_Lock;
		case SDLK_PAUSE: return eKey_Pause;
		case SDLK_HOME: return eKey_Home;
		case SDLK_INSERT: return eKey_Insert;
		case SDLK_PAGEUP: return eKey_Page_Up;
		case SDLK_PAGEDOWN: return eKey_Page_Down;
		case SDLK_DELETE: return eKey_Delete;
		case SDLK_END: return eKey_End;

		case SDLK_NUMLOCKCLEAR: return eKey_Num_Lock;
		case SDLK_KP_0: return eKey_Num_0;
		case SDLK_KP_1: return eKey_Num_1;
		case SDLK_KP_2: return eKey_Num_2;
		case SDLK_KP_3: return eKey_Num_3;
		case SDLK_KP_4: return eKey_Num_4;
		case SDLK_KP_5: return eKey_Num_5;
		case SDLK_KP_6: return eKey_Num_6;
		case SDLK_KP_7: return eKey_Num_7;
		case SDLK_KP_8: return eKey_Num_8;
		case SDLK_KP_9: return eKey_Num_9;
		case SDLK_KP_MULTIPLY: return eKey_Num_Mul;
		case SDLK_KP_DIVIDE: return eKey_Num_Div;
		case SDLK_KP_MINUS: return eKey_Num_Sub;
		case SDLK_KP_PLUS: return eKey_Num_Add;
		case SDLK_KP_ENTER: return eKey_Num_Enter;
		case SDLK_KP_PERIOD: return eKey_Num_Period;

		default:
			return eKey_LastEnum;
		}
	}
}
