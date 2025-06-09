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
		
		
		

		return true;
	}


=======
#include "graphics/Graphics.h"
#include "video/VideoSDL.h"

#include "GL/glew.h"

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
		


		return true;
	}


>>>>>>> e1637d263fa7994d5ce3a7276463df609a269e2f
}