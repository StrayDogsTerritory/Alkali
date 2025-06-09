#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

<<<<<<< HEAD
#include "GL/glew.h"
=======
#include "SDL3/SDL.h"


>>>>>>> e1637d263fa7994d5ce3a7276463df609a269e2f

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
