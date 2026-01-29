#ifndef ALK_SYSTEMINTERFACE_H
#define ALK_SYSTEMINTERFACE_H

#include "system/Platform.h"

namespace alk {

	class iScript;

	class iSystem
	{
	public:
		virtual ~iSystem() {}

		virtual iScript* CreateScript()=0;
	};
}

#endif
