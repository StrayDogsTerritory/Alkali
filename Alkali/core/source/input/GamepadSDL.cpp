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
			
			mvGamepadButtonArray.resize(eGamepadButton_LastEnum); //fix crashes related from buffer overflowing
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

		case SDL_GAMEPAD_BUTTON_DPAD_UP: return eGamepadButton_Hat_Up;
		case SDL_GAMEPAD_BUTTON_DPAD_DOWN: return eGamepadButton_Hat_Down;
		case SDL_GAMEPAD_BUTTON_DPAD_LEFT: return eGamepadButton_Hat_Left;
		case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: return eGamepadButton_Hat_Right;

		case SDL_GAMEPAD_BUTTON_LEFT_STICK: return eGamepadButton_Left_Stick;
		case SDL_GAMEPAD_BUTTON_RIGHT_STICK: return eGamepadButton_Right_Stick;

		case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: return eGamepadButton_Left_Trigger;
		case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return eGamepadButton_Right_Trigger;
		
		case SDL_GAMEPAD_BUTTON_TOUCHPAD: return eGamepadButton_Touchpad;

		case SDL_GAMEPAD_BUTTON_GUIDE: return eGamepadButton_Special_3;
		case SDL_GAMEPAD_BUTTON_START: return eGamepadButton_Options;
		case SDL_GAMEPAD_BUTTON_BACK: return eGamepadButton_Social;
		default: return eGamepadButton_LastEnum;
		}
	}
}