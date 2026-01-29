#include "input/Input.h"
#include "input/InputInterface.h"
//#include "SDL3/SDL.h"
#include "engine/LogWriter.h"
#include "engine/Engine.h"

namespace alk {

	cInput::cInput(iInput* apInputInterfaec) : iUpdateable("Input")
	{

		mpInput = apInputInterfaec;
		mbQuitting = false;

		SetRelativeMouse(false);

		mpKeyboard = mpInput->CreateKeyboard();
		mLstDevice.push_back(mpKeyboard);
		mpMouse = mpInput->CreateMouse();
		mLstDevice.push_back(mpMouse);

		// @TODO: what to do about controllers?
	}

	cInput::~cInput()
	{
		if(mpKeyboard)alkDelete(mpKeyboard);
		if(mpMouse)alkDelete(mpMouse);

		DeleteAllMap(mMapActionName);
//		DeleteAllMap(mMapActionID);
		DeleteAll(mLstGamepad);
	}

	void cInput::OnUpdate(float afStep)
	{
		mpInput->Update(afStep);

		
			for (tInputDeviceIt it = mLstDevice.begin(); it != mLstDevice.end(); ++it)
			{
				(*it)->Update();
			}

			for (tActionNameMapIterator it = mMapActionName.begin(); it != mMapActionName.end(); ++it)
			{
				it->second->Update(afStep);
			}
		
	}

	cAction* cInput::CreateAction(const tString& asName, int alID)
	{
		cAction* pAction = alkNew(cAction, (asName, alID, this));

		tActionNameMap::value_type valName = tActionNameMap::value_type(asName, pAction);
		mMapActionName.insert(valName);

		tActionIDMap::value_type valID = tActionIDMap::value_type(alID, pAction);
		mMapActionID.insert(valID);

		return pAction;
	}

	void cInput::DestroyAction(cAction* apAction)
	{
	}

	cAction* cInput::GetAction(const tString& asName)
	{
		tActionNameMapIterator it = mMapActionName.find(asName);

		if (it == mMapActionName.end())
		{
			return NULL;
		}

		return it->second;
	}

	cAction* cInput::GetAction(int alID)
	{
		tActionIDMapIterator it = mMapActionID.find(alID);

		if (it == mMapActionID.end())
		{
			return NULL;
		}

		return it->second;
	}

	bool cInput::IsTriggered(const tString& asName)
	{
		cAction* pAction = GetAction(asName);
		if (pAction->IsTriggered())
		{
			return true;
		}
		return false;
	}

	bool cInput::BecameTriggered(const tString& asName)
	{
		cAction* pAction = GetAction(asName);
		if (pAction->BecameTriggered())
		{
			return true;
		}

		return false;
	}

	void cInput::ResetGamepads()
	{
		// clear out the gamepads from our lists
		tGamepadListIt it = mLstGamepad.begin();
		for (; it != mLstGamepad.end(); ++it)
		{
			mLstDevice.remove(*it);
		}
		DeleteAll(mLstGamepad);

		//Add any new ones in
		for (int i = 0; i < mpInput->GetNumberOfGamepads(); ++i)
		{
			iGamepad* pGamepad = mpInput->CreateGamepad(mpInput->GetGamepadID(),i);

			// make sure its valid @TODO: maybe do this differently? Figure it out later
			if (pGamepad->GetName() == "")
			{
				alkDelete(pGamepad);
				Error("Gamepad index '%d' Could not be created!\n", i);
			}

			// test
			Log("Gamepad Name: '%s'\n", pGamepad->GetName().c_str());

			mLstGamepad.push_back(pGamepad);
			mLstDevice.push_back(pGamepad);
		}
	}

	void cInput::DeviceAdded()
	{
		ResetGamepads();
	}

	void cInput::DeviceRemoved()
	{
		ResetGamepads();
	}

	iGamepad* cInput::GetGamepad(int alIndex)
	{
		tGamepadListIt it = mLstGamepad.begin();
		for (; it != mLstGamepad.end(); ++it)
		{
			iGamepad* pGamepad = *it;
			if (pGamepad->GetIndex() == alIndex)
			{
				return pGamepad;
			}
		}
		return NULL;
	}


	bool cInput::GetIsQuit()
	{
		return mpInput->GetIsQuit();
	}


	void cInput::SetRelativeMouse(bool abX)
	{
		mpInput->SetRelativeMouse(abX);
	}

	
}