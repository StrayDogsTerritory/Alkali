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

	bool cTextureGL::CreateTextureFromBitmap( cBitmap* apBitmap)
	{

		GenerateTextureIDs(1);

		return CreateTextureFromBitmapIdx(apBitmap, 0);
	}



	bool cTextureGL::CreateMipMaps()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		return true;
	}

	bool cTextureGL::CreateTextureFromBitmapIdx(cBitmap* apBitmap, int alIdx)
	{
		if (mTextureType == eTextureType_CubeMap)
		{
			// do nothing for now...
		}

		else
		{

			bool bRet = CreateTexture(alIdx,apBitmap->GetData(0,0), apBitmap->GetNumberMipMaps(), apBitmap->GetDimensions(),apBitmap->GetBitmapFormat(), apBitmap->GetIsCompressed());

			return bRet;
		}
		

		return false;
	}

	

	bool cTextureGL::CreateTexture(int alID, cBitmapData* apBitmapData, int alNumberOfMipMaps, tVector3l avSize, eBitmapFormat aFormat, bool abIsCompressed)
	{
		GLenum Type = EnumToGLTextureType(mTextureType);
		GLenum Format = EnumToGLPixelFormat(aFormat);

		mvDimensions = avSize;

		glBindTexture(Type, alID);

		bool bRet = true;
		tVector3l vResize = mvDimensions;

		for (int i = 0; i < alNumberOfMipMaps; ++i)
		{
			if (vResize.x == 0) vResize.x = 1;
			if (vResize.y == 0) vResize.y = 1;
			if (vResize.z == 0) vResize.z = 1;

			unsigned char* pData = apBitmapData[i].mpData;
			size_t lSize = apBitmapData[i].mlSize;

			if (!CopyTextureDataToGL(Type,Format, pData,lSize,vResize, abIsCompressed))
			{
				bRet = false;
				break;
			}

			vResize.x >>= 1;
			vResize.y >>= 1;
			vResize.z >>= 1;

		}

		if (bRet == false)

		return true;
	}

	bool cTextureGL::CopyTextureDataToGL(GLenum TypeGL, GLenum FormatGL, int alMipMapLevel, unsigned char* apData, size_t alDataSize, tVector3l avSize, bool abIsCompressed)
	{
		while (glGetError() != GL_NO_ERROR); // clear the error log

		mlMemorySize += alDataSize;

		if (abIsCompressed)
		{
			if (mTextureType == eTextureType_1D)
			{
				glCompressedTexImage1D()
			}
		}
	}

	void cTextureGL::SetupGLFromBitmap(cBitmap* apBitmap)
	{
		// @TODO: DO NOT HARD CODE ANY OF THIS!!!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}


	void cTextureGL::Bind(int alUnit)
	{
		glActiveTexture(GL_TEXTURE0 + alUnit);

		glBindTexture(GL_TEXTURE_2D, mvIDs[0]);
		//glEnable(GL_TEXTURE_2D);
	}



	GLenum cTextureGL::EnumToGLPixelFormat(eBitmapFormat aFormat)
	{
		switch (aFormat)
		{
		case eBitmapFormat_RGB: return GL_RGB;
		case eBitmapFormat_RGBA: return GL_RGBA;

		default: return -1;
		}
	}

	GLenum cTextureGL::EnumToGLTextureType(eTextureType aTextureType)
	{
		switch (aTextureType)
		{
		case eTextureType_1D: return GL_TEXTURE_1D;
		case eTextureType_2D: return GL_TEXTURE_2D;
		case eTextureType_Rect: return GL_TEXTURE_RECTANGLE;
		case eTextureType_CubeMap: return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		case eTextureType_3D: return GL_TEXTURE_3D;
		}
	}

	GLenum cTextureGL::EnumToGLTextureWrapMode(eTextureWrappingMode aTextureWrappingMode)
	{
		switch (aTextureWrappingMode)
		{
		case eTextureWrappingMode_Repeat: return GL_REPEAT;
		case eTextureWrappingMode_Mirrored: return GL_MIRRORED_REPEAT;
		case eTextureWrappingMode_ClampToEdge: return GL_CLAMP_TO_EDGE;
		case eTextureWrappingMode_ClampToBorder: return GL_CLAMP_TO_BORDER;
		}
	}
	GLenum cTextureGL::EnumToGLTextureFilter(eTextureFilter aTextureFilter)
	{
		switch (aTextureFilter)
		{
		case eTextureFilter_Bilinear: return GL_LINEAR;
		case eTextureFilter_Trilinear: return GL_LINEAR_MIPMAP_LINEAR;
		}
	}
}