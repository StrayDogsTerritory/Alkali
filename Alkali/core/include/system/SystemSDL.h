#ifndef ALK_SYSTEMSDL_H
#define ALK_SYSTEM_SDL_H

#include "system/SystemInterface.h"

namespace alk {

	class cSystemSDL : public iSystem
	{
	public:
		cSystemSDL();
		~cSystemSDL();

		iScript* CreateScript();
	};
}
#endif
