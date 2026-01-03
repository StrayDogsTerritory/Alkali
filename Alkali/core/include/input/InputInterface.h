#ifndef ALK_INPUTINTERFACE_H
#define ALK_INPUTINTERFACE_H

namespace alk {

	class iGamepad;
	class iMouse;
	class iKeyboard;

	class iInput
	{
	public:
		virtual ~iInput() {}

		virtual void Update(float afStep) = 0;

		virtual bool GetIsQuit()=0;

		virtual int GetNumberOfGamepads()=0;

		virtual iKeyboard* CreateKeyboard() = 0;
		virtual iMouse* CreateMouse() = 0;
		virtual iGamepad* CreateGamepad(int alID, int alIndex) = 0;

		virtual void SetRelativeMouse(bool abX)=0;

		virtual int GetGamepadID()=0;

	protected:
	
	};
}

#endif