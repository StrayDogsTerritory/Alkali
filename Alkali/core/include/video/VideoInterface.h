#ifndef ALK_VIDEOINTERFACE_H
#define ALK_VIDEOINTERFACE_H

#include "SDL3/SDL_video.h"

namespace alk {

	class iVideo
	{
	public:
		virtual ~iVideo() {};
		virtual bool Init(int alHeight, int alWidth, int alWindowMode) = 0;
		
		virtual SDL_Window* GetWindow() = 0;

	
		
	};

}
#endif
