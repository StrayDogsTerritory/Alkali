#ifndef ALK_GRAPHICS_H
#define ALK_GRAPHICS_H

<<<<<<< HEAD
#include "GL/glew.h"
=======
#include "SDL3/SDL.h"


>>>>>>> e1637d263fa7994d5ce3a7276463df609a269e2f

=======
>>>>>>> parent of e1637d2 (technically broken, need to add buffer swapping manually, because for some reason the screen pointer hates me. Fuck you screen pointer, make my life easier you shitty little thing. Fuck you so much you pathetic little pointer.)
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
