#include "input/MouseSDL.h"
#include "input/InputSDL.h"

#include "engine/LogWriter.h"

namespace alk {

	cMouseSDL::cMouseSDL(cInputSDL* apInputSDL)
	{
		mpInputSDL = apInputSDL;
		mvMouseButtonArray.resize(eMouseButton_LastEnum);
		mbActive = false;

		//clear the array to start
		mvMouseButtonArray.assign(mvMouseButtonArray.size(), false);
	}

	cMouseSDL::~cMouseSDL()
	{
	}

	void cMouseSDL::Update()
	{
		mbActive = false;

		std::list<SDL_Event>::iterator it = mpInputSDL->mLstSDLEvents.begin();
		for (; it != mpInputSDL->mLstSDLEvents.end(); it++)
		{
			SDL_Event* pEvent = &(*it);
			if (pEvent->type == SDL_EVENT_MOUSE_MOTION)
			{
				mbActive = true;

				mvMousePos.x = pEvent->motion.x;
				mvMousePos.y = pEvent->motion.y;

			}
			else if (pEvent->type == SDL_EVENT_MOUSE_BUTTON_DOWN || pEvent->type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
				mbActive = true;

				eMouseButton Button = SDLToKey(pEvent->button.button);
				mvMouseButtonArray[Button] = pEvent->button.down ? true : false;
			}
		}
	}

	bool cMouseSDL::ButtonDown(eMouseButton aKey)
	{
		return mvMouseButtonArray[aKey] == true;
	}

	bool cMouseSDL::MouseActive()
	{
		return mbActive;
	}

	tVector2l cMouseSDL::GetMousePos()
	{
		return mvMousePos;
	}

	eMouseButton cMouseSDL::SDLToKey(int alKey)
	{
		switch (alKey)
		{
			// core mouse buttons
		case SDL_BUTTON_LEFT: return eMouseButton_Left;
		case SDL_BUTTON_RIGHT: return eMouseButton_Right;
		case SDL_BUTTON_MIDDLE: return eMouseButton_Middle;
			// special buttons
		case SDL_BUTTON_X1: return eMouseButton_4;
		case SDL_BUTTON_X2: return eMouseButton_5;
		default:
			return eMouseButton_LastEnum;
		}
	}
}