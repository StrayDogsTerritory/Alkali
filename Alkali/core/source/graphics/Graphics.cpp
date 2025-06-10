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


}