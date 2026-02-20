#include "graphics/TextureGL.h"
#include "graphics/Bitmap.h"

#include "engine/LogWriter.h"

#include <GL/glew.h>

namespace alk {

	cTextureGL::cTextureGL(const tString& asName, eTextureType aType, eTextureFilter aFilter, eTextureWrappingMode aMode) : iTexture(asName)
	{
		// do something here...
		mlMemorySize = 0;
		msName = asName;

		mbUseMipMaps = false;
		mFilter = aFilter;
		mTextureType = aType;
		mWrappingMode = aMode;

		// get around to this later
		mfAnisotropicFilteringDegree = 0.0f;
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
		mbUseMipMaps = apBitmap->GetNumberMipMaps() > 1 ? true : false;

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

			if (CopyTextureDataToGL(aFormat, i, pData,lSize,vResize, abIsCompressed) == false)
			{
				bRet = false;
				break;
			}

			vResize.x >>= 1;
			vResize.y >>= 1;
			vResize.z >>= 1;

		}
		if (bRet == false) return false;

		// setup the texture settings 
		SetupTextureProperties(alID);
		return true;
	}

	bool cTextureGL::CopyTextureDataToGL(eBitmapFormat aFormat, int alMipMapLevel, unsigned char* apData, size_t alDataSize, tVector3l avSize, bool abIsCompressed)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLenum lType = EnumToGLTextureType(mTextureType);
		GLenum lFormat = EnumToGLPixelFormat(aFormat);

		while (glGetError() != GL_NO_ERROR); // clear the error log

		mlMemorySize += alDataSize;

		if (abIsCompressed)
		{
			if (mTextureType == eTextureType_1D)
			{
				glCompressedTexImage1D(lType, alMipMapLevel, lFormat, avSize.x,0, alDataSize, apData);
			}
			else if (mTextureType == eTextureType_2D || mTextureType == eTextureType_CubeMap || mTextureType == eTextureType_Rect)
			{
				glCompressedTexImage2D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, 0, alDataSize, apData);
			}
			else if (mTextureType == eTextureType_3D)
			{
				glCompressedTexImage3D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, avSize.z, 0, alDataSize, apData);
			}
		}
		else // uncompressed image
		{
			if (mTextureType == eTextureType_1D)
			{
				glTexImage1D(lType, alMipMapLevel, lFormat, avSize.x, 0, lFormat, GL_UNSIGNED_BYTE, apData);
			}
			else if (mTextureType == eTextureType_2D || mTextureType == eTextureType_CubeMap || mTextureType == eTextureType_Rect)
			{
				glTexImage2D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, 0, lFormat, GL_UNSIGNED_BYTE, apData);
			}
			else if (mTextureType == eTextureType_3D)
			{
				glTexImage3D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, avSize.z, 0, GL_UNSIGNED_BYTE, lFormat, apData);
			}
		}

		GLint lInt = glGetError();

		if (glGetError() != GL_NO_ERROR) { Log("%u\n", glGetError()); return false; }

		return true;
	}

	void cTextureGL::SetupTextureProperties(int alIdx)
	{
		GLenum lType = EnumToGLTextureType(mTextureType);
		GLenum lWrapMode = EnumToGLTextureWrapMode(mWrappingMode);

		// test 
		lWrapMode = GL_CLAMP_TO_EDGE;

		glBindTexture(lType, alIdx);

		// texture filtering
		if (mFilter == eTextureFilter_Trilinear && mbUseMipMaps)
		{
			glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(lType, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(lType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		// texture wrapping
		glTexParameteri(lType, GL_TEXTURE_WRAP_S, lWrapMode);
		glTexParameteri(lType, GL_TEXTURE_WRAP_T, lWrapMode);
		glTexParameteri(lType, GL_TEXTURE_WRAP_R, lWrapMode);

		while (glGetError() != GL_NO_ERROR)
		{
			Log("'%u'\n", glGetError());
		}

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

		case eBitmapCompressionFormat_DXT1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		case eBitmapCompressionFormat_DXT3: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		case eBitmapCompressionFormat_DXT5: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		case eBitmapCompressionFormat_3DC: return GL_3DC_XY_AMD;
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