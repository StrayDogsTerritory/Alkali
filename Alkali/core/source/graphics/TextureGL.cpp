#include "graphics/TextureGL.h"
#include "graphics/Bitmap.h"

#include <GL/glew.h>

namespace alk {

	cTextureGL::cTextureGL() : iTexture()
	{
		// do something here...
		
	}

	cTextureGL::~cTextureGL()
	{
		glDeleteTextures(mvIDs.size(), (GLuint*)&mvIDs[0]);
	}

	void cTextureGL::GenerateTextureIDs(int alNumToGen)
	{
		int lNewTextures = mvIDs.size() - alNumToGen;

		glGenTextures(alNumToGen, (GLuint*)&mvIDs[lNewTextures]);
	}

	bool cTextureGL::CreateTexture()
	{
		cBitmap* pBitmap = apBitmap;

		return false;
	}

}