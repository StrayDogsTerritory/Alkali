#ifndef ALK_INPUT_H
#define ALK_INPUT_H

#include "engine/Updateable.h"

#include "system/String.h"

#include "input/InputDevice.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "input/Gamepad.h"
#include "input/Action.h"

#include <list>
#include <map>

namespace alk {

	class iInput;
		
	typedef std::list<iInputDevice*> tInputDeviceLst;
	typedef tInputDeviceLst::iterator tInputDeviceIt;

	typedef std::multimap<tString, cAction*> tActionNameMap;
	typedef tActionNameMap::iterator tActionNameMapIterator;

	typedef std::multimap<int, cAction*> tActionIDMap;
	typedef tActionIDMap::iterator tActionIDMapIterator;

	typedef std::list<iGamepad*> tGamepadList;
	typedef tGamepadList::iterator tGamepadListIt;

	class cInput : public iUpdateable
	{
	public:
		cInput(iInput* apInputInterface);
		~cInput();

		bool Init();

		void OnUpdate(float afStep);

		bool GetIsQuit();

		bool GetInputFrozen() { return mbInputFrozen; }
		void SetInputFrozen(bool abX) { mbInputFrozen = abX; }
		void SetRelativeMouse(bool abX);

		cAction* CreateAction(const tString& asName, int alID = -1);
		void DestroyAction(cAction* apAction);

		cAction* GetAction(const tString& asName);
		cAction* GetAction(int alID);

		bool IsTriggered(const tString& asName);
		bool IsTriggered(int alID);

		bool BecameTriggered(const tString& asName);
		bool BecameTriggered(int alID);

		void ResetGamepads();

		void CreateInputEventFromInput();

		void DeviceAdded();
		void DeviceRemoved();

		iMouse* GetMouse() { return mpMouse; }
		iKeyboard* GetKeyboard() { return mpKeyboard; }
		iGamepad* GetGamepad(int alIndex);

	private:
		bool mbInputFrozen;
		// test some bullshit SDL 3 throws at me
		bool mbFirstTime;

		iInput* mpInput;
		bool mbQuitting;
		
		tInputDeviceLst mLstDevice;
		tActionNameMap mMapActionName;
		tActionIDMap mMapActionID;

		iKeyboard* mpKeyboard;
		iMouse* mpMouse;
		tGamepadList mLstGamepad;

		
		
	};

}
#endif
