#include "graphics/TextureGL.h"
#include "graphics/Bitmap.h"

#include <GL/glew.h>

namespace alk {

	cTextureGL::cTextureGL(const tString& asName) : iTexture(asName)
	{
		// do something here...
		mlMemorySize = 0;
		msName = asName;
	}

	cTextureGL::~cTextureGL()
	{
		for (int i = 0; i < mvIDs.size(); ++i)
		{
			glDeleteTextures(1, (GLuint*)&mvIDs[i]);
		}
	}

	void cTextureGL::GenerateTextureIDs(int alNumToGen)
	{
		int lNewTextures = alNumToGen - mvIDs.size();
		mvIDs.resize(alNumToGen);
		glGenTextures(alNumToGen, (GLuint*)&mvIDs[alNumToGen-lNewTextures]);
	}

	bool cTextureGL::CreateTextureFromBitmap(tVector3l avDimensions, cBitmap* apBitmap)
	{
		mvDimensions = apBitmap->GetDimensions();
		GenerateTextureIDs(1);
		glBindTexture(GL_TEXTURE_2D, mvIDs[0]);

		SetupGLFromBitmap(apBitmap);

		cBitmapData* pData = apBitmap->GetData(0, 0);
		if (pData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, apBitmap->GetBitmapFormat(), apBitmap->GetLength(), apBitmap->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
			CreateMipMaps();
		}

		return true;
	}

	bool cTextureGL::CreateMipMaps()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		return true;
	}

	void cTextureGL::SetupGLFromBitmap(cBitmap* apBitmap)
	{
		// @TODO: DO NOT HARD CODE ANY OF THIS!!!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

}