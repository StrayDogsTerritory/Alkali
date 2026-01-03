#include "input/InputSDL.h"
#include "input/InputInterface.h"
#include "input/Gamepad.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "input/KeyboardSDL.h"
#include "input/MouseSDL.h"
#include "input/GamepadSDL.h"

#include "engine/LogWriter.h"
#include "engine/Engine.h"

#include "graphics/GraphicsInterface.h"

namespace alk {

	cInputSDL::cInputSDL(iGraphics* apGraphics)
	{
		mpGraphics = apGraphics;

		if (!SDL_InitSubSystem(SDL_INIT_GAMEPAD))
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
			Log("Event: %u\n", lEvent.type);

			if (lEvent.type == SDL_EVENT_QUIT)
			{
				mbQuitting = true;
			}
			if (lEvent.type == SDL_EVENT_WINDOW_RESIZED)
			{
			}

			if (lEvent.type == SDL_EVENT_GAMEPAD_ADDED)
			{
				cEngine::SetDevicePlugged();
				mlGamepadJoyID = lEvent.gdevice.which;
			}
			if (lEvent.type == SDL_EVENT_GAMEPAD_REMOVED)
			{
				cEngine::SetDeviceUnplugged();
			}

			else
				mLstSDLEvents.push_back(lEvent);
		}
	}

	iKeyboard* cInputSDL::CreateKeyboard()
	{
		return alkNew(cKeyboardSDL, (this));
	}

	iMouse* cInputSDL::CreateMouse()
	{
		return alkNew(cMouseSDL, (this));
	}

	iGamepad* cInputSDL::CreateGamepad(int alID, int alIndex)
	{
		return alkNew(cGamepadSDL, (this, alID, alIndex));
	}

	void cInputSDL::SetRelativeMouse(bool abX)
	{
		mpGraphics->SetRelativeMouse(abX);
	}

	int cInputSDL::GetNumberOfGamepads()
	{
		int lX = 0;
		SDL_GetGamepads(&lX);
		
		return lX;
	}

	int cInputSDL::GetGamepadID()
	{
		return mlGamepadJoyID;
	}

	bool cInputSDL::GetIsQuit()
	{
		return mbQuitting;
	}
}