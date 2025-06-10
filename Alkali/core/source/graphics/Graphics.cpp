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
		
		
		

		return true;
	}


>>>>>>> parent of e1637d2 (technically broken, need to add buffer swapping manually, because for some reason the screen pointer hates me. Fuck you screen pointer, make my life easier you shitty little thing. Fuck you so much you pathetic little pointer.)
}