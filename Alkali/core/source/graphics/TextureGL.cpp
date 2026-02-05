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
		int lNewTextures = alNumToGen - mvIDs.size();
		mvIDs.resize(alNumToGen);
		glGenTextures(alNumToGen, (GLuint*)&mvIDs[alNumToGen-lNewTextures]);
	}

	bool cTextureGL::CreateTexture()
	{
		cBitmap* pBitmap;
		pBitmap->Get

		return false;
	}

}