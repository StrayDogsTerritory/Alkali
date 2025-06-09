#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

#include "SDL3/SDL.h"



namespace alk {

	class iVideo;

	class cGraphics
	{
	public:
		cGraphics();
		~cGraphics();

		bool InitOpenGL();

	private:

		iVideo* mpVideo;

	};

}

#endif
