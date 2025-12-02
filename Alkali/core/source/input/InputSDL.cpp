#include "input/InputSDL.h"
#include "input/InputInterface.h"
#include "input/Gamepad.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

#include "engine/LogWriter.h"

namespace alk {

	cInputSDL::cInputSDL()
	{
		if (SDL_InitSubSystem(SDL_INIT_GAMEPAD))
		{
			Error("SDL failed to init input! Reason: '%s'\n", SDL_GetError());
		}
		mbQuitting = false;
	}

	cInputSDL::~cInputSDL()
	{

	}

	void cInputSDL::Update(float afStep)
	{
		SDL_Event lEvent;
		while (SDL_PollEvent(&lEvent))
		{
			if (lEvent.type == SDL_EVENT_QUIT)
			{
				mbQuitting = true;
			}
			if (lEvent.type == SDL_EVENT_WINDOW_RESIZED)
			{
				Log("Window Resized to '%u' '%u'", lEvent.window.data1, lEvent.window.data2);
			}
			else
				Log("SDL event! '%u'\n", lEvent.type);
				mLstSDLEvents.push_back(lEvent);
		}
	}

	iKeyboard* cInputSDL::CreateKeyboard()
	{
		return NULL;
	}

	iMouse* cInputSDL::CreateMouse()
	{
		return NULL;
	}

	iGamepad* cInputSDL::CreateGamepad()
	{
		return NULL;
	}


	bool cInputSDL::GetIsQuit()
	{
		return mbQuitting;
	}
}