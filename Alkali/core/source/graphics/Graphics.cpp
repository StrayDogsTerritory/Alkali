<<<<<<< HEAD
#include "graphics/Graphics.h"

namespace alk {

	cGraphics::cGraphics()
	{}

	cGraphics::~cGraphics()
	{}


	bool cGraphics::InitOpenGL()
	{

		

		// temp hard coding; want to get a triangle on the screen, but not actually do any more work than that.
		
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		return true;
	}


=======
#include "graphics/Graphics.h"
<<<<<<< HEAD
=======
#include "video/VideoSDL.h"

#include "GL/glew.h"
>>>>>>> d9dde0ee5dadd39e1b8cc25b534e2432db9054c2

namespace alk {

	cGraphics::cGraphics()
	{ 
	
	}

	cGraphics::~cGraphics()
	{
	
	}


	bool cGraphics::InitOpenGL()
	{
		// temp hard coding; want to get a triangle on the screen, but not actually do any more work than that.
		
<<<<<<< HEAD
		
		

=======
		float vVerts[] =
		{
			0.0, 0.5, 0.0,
			-0.5, -0.5, 0.0,
			0.5, -0.5, 0.0
		};
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vVerts );
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);

		SDL_GL_SwapWindow(mpVideo->GetWindow());
		


>>>>>>> d9dde0ee5dadd39e1b8cc25b534e2432db9054c2
		return true;
	}


<<<<<<< HEAD
>>>>>>> parent of e1637d2 (technically broken, need to add buffer swapping manually, because for some reason the screen pointer hates me. Fuck you screen pointer, make my life easier you shitty little thing. Fuck you so much you pathetic little pointer.)
=======
>>>>>>> e1637d263fa7994d5ce3a7276463df609a269e2f
>>>>>>> d9dde0ee5dadd39e1b8cc25b534e2432db9054c2
}