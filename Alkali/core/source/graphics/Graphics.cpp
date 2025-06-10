#include "graphics/Graphics.h"
#include "video/VideoSDL.h"


namespace alk {

	cGraphics::cGraphics()
	{ 
	
	}

	cGraphics::~cGraphics()
	{
	
	}


	bool cGraphics::InitOpenGL()
	{
		glEnableClientState(GL_VERTEX_ARRAY);


		return true;
	}

void	cGraphics::DrawTriangle()
	{
		float vVerts[] =
		{
			0.0, 0.5, 0.0,
		};

		glVertexPointer(3, GL_FLOAT, 0, vVerts);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);

		mpVideoSDL->SwapBuffer();
	}



}