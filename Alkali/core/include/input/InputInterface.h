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

		virtual void Update(float afTimeStep) = 0;

		virtual bool GetIsQuit()=0;

		virtual iKeyboard* CreateKeyboard() = 0;
		virtual iMouse* CreateMouse() = 0;
		virtual iGamepad* CreateGamepad() = 0;

	protected:
	};
}

#endif