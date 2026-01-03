#include "input/KeyboardSDL.h"

#include "engine/LogWriter.h"

namespace alk {

	cKeyboardSDL::cKeyboardSDL(cInputSDL* apInputSDL)
	{
		mpInputSDL = apInputSDL;
		mvKeyPressed.resize(eKey_LastEnum);

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

		default:
			return eKey_LastEnum;
		}
	}
}
