#ifndef ALK_VIDEOINTERFACE_H
#define ALK_VIDEOINTERFACE_H

#include "SDL3/SDL_video.h"

namespace alk {

	class iVideo
	{
	public:
		virtual ~iVideo() {};
		virtual bool Init(int alHeight, int alWidth, int alWindowMode) = 0;
		virtual bool InitOpenGL() = 0;

		virtual void SwapBuffer() = 0;
	
		virtual bool SetCursorVisibility(bool abx) = 0;
		virtual bool SetWindowFullscreen(bool abx) = 0;
		virtual bool SetWindowBorderless(bool abx) = 0;
	};

}
#endif
