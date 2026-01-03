#ifndef ALK_INPUTEVENT_H
#define ALK_INPUTEVENT_H

#include "input/Input.h"

namespace alk {

	class iInputEvent
	{
	public:
		iInputEvent() {}
		virtual ~iInputEvent() {}

		virtual bool IsTriggered()=0;


	protected:
	};
}

#endif
