#include "input/GamepadSDL.h"
#include "input/Gamepad.h"

#include "graphics/Colour.h"

#include "engine/LogWriter.h"

namespace alk {

	cGamepadSDL::cGamepadSDL(cInputSDL* apInputSDL, int alID, int alIndex) : iGamepad(alID,alIndex)
	{
		mpInputSDL = apInputSDL;
		mlIndex = alIndex;
			
		mpHandle = SDL_OpenGamepad(alID);
		if (!mpHandle)
		{
			Error("Controller Error! '%s'\n", SDL_GetError());
		}
		
		if (mpHandle)
		{
			SDL_Joystick* pStick = SDL_GetGamepadJoystick(mpHandle);
			
			msName = SDL_GetGamepadName(mpHandle);
			
			mvGamepadButtonArray.resize(eGamepadButton_LastEnum);
			mvGamepadButtonArray.assign(mvGamepadButtonArray.size(), false);
			
		}
	}

	cGamepadSDL::~cGamepadSDL()
	{
		if (mpHandle)
		{
			// reset the LED and rumble to their normal values
			SDL_SetGamepadLED(mpHandle, 0, 0, 0);

			SDL_RumbleGamepad(mpHandle, 0, 0, 0);

			//close the gamepad
			SDL_CloseGamepad(mpHandle);
		}
	}

	void cGamepadSDL::Update()
	{
		Log("Updating Controller!\n");

		std::list<SDL_Event>::iterator it = mpInputSDL->mLstSDLEvents.begin();
		for (; it != mpInputSDL->mLstSDLEvents.end(); ++it)
		{
			SDL_Event* pEvent = &(*it);
		//	Log("SDL event: '%d'\n", pEvent->type);

			if (pEvent->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || pEvent->type == SDL_EVENT_GAMEPAD_BUTTON_UP)
			{
				eGamepadButton Button = SDLToButton(pEvent->gbutton.button);
				mvGamepadButtonArray[Button] = pEvent->gbutton.down ? true : false;
			}
		}
	}

	bool cGamepadSDL::ButtonDown(eGamepadButton aKey)
	{
		if (mpHandle) 
			return mvGamepadButtonArray[aKey] == true;
		return false;
	}

	bool cGamepadSDL::ControllerActive()
	{
		for (int i = 0; i < eGamepadButton_LastEnum; ++i)
		{
			if (mvGamepadButtonArray[(eGamepadButton)i] == true)
			{
				return true;
			}
		}
		return false;
	}

	void cGamepadSDL::RumbleController(int alLeftRumble, int alRightRumble, int alDuration)
	{
		SDL_RumbleGamepad(mpHandle, alLeftRumble, alRightRumble, alDuration);
	}

	void cGamepadSDL::ChangeLEDColour(cColour aCol)
	{
		SDL_SetGamepadLED(mpHandle, aCol.r,aCol.g, aCol.b);
	}

	eGamepadButton cGamepadSDL::SDLToButton(int alKey)
	{
		switch (alKey)
		{
		case SDL_GAMEPAD_BUTTON_SOUTH: return eGamepadButton_0;
		case SDL_GAMEPAD_BUTTON_EAST: return eGamepadButton_1;
		case SDL_GAMEPAD_BUTTON_WEST: return eGamepadButton_2;
		case SDL_GAMEPAD_BUTTON_NORTH: return eGamepadButton_3;

		default: return eGamepadButton_LastEnum;
		}
	}
}