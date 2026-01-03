#ifndef ALK_INPUTDEVICE_H
#define ALK_INPUTDEVICE_H

namespace alk {

	class iInputDevice
	{
	public:
		iInputDevice() {}


		virtual void Update()=0;
	protected:
	};

}

#endif
