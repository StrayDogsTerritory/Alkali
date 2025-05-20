#ifndef ALK_VIDEOSDL_H
#define ALK_VIDEOSDL_H

#include "video/VideoInterface.h"
#include "SDL3/SDL_video.h"

namespace alk {

	class cVideoSDL : public iVideo
	{
	public:
		cVideoSDL();
		~cVideoSDL();
		bool Init(int alHeight, int alWidth, bool abIsFullScreen);
	private:

		SDL_Window* mpSDLWindow;
	};

}
#endif
