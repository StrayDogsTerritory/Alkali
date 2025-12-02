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
				Log("TEST: Numpad:'%s' pressed\n", EnumToString(Key));
				
				Log("\nKeyboard Array\n");
				for (int i = 0; i < mvKeyPressed.size(); ++i)
				{
					Log("Key '%u', state: '%u'\n", i, mvKeyPressed[i]);
				}
			}
		}
	}

	void cKeyboardSDL::ResetKeysPressed()
	{
		mvKeyPressed.assign(mvKeyPressed.size(), false);
	}

	eKey cKeyboardSDL::SDLCodeToKey(int alKey)
	{
		switch (alKey)
		{
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
