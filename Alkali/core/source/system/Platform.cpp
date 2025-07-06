#include "system/Platform.h"
#include "SDL3/SDL_timer.h"

namespace alk {

	unsigned int alk::cPlatform::GetAppTime()
	{ 

		return SDL_GetTicks();
	}

}
