#ifndef ALK_INPUT_H
#define ALK_INPUT_H

#include "engine/Updateable.h"

#include "input/InputDevice.h"

#include <list>

namespace alk {

	class iInput;
		
	typedef std::list<iInputDevice*> tInputDeviceLst;
	typedef tInputDeviceLst::iterator tInputDeviceIt;

	class cInput : public iUpdateable
	{
	public:
		cInput(iInput* apInputInterface);
		~cInput();

		void OnUpdate(float afStep);

		bool GetIsQuit();

	private:
		iInput* mpInput;
		void ProcessEvent();
		bool mbQuitting;
		tInputDeviceLst mLstDevice;
	};

}
#endif
