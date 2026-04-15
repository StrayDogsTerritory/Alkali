#include "graphics/TextureGL.h"
#include "graphics/Bitmap.h"

#include "engine/LogWriter.h"

#include <GL/glew.h>

namespace alk {

	cTextureGL::cTextureGL(const tString& asName, eTextureType aType, eTextureFilter aFilter, eTextureWrappingMode aMode) : iTexture(asName)
	{
		// do something here...
		mlMemorySize = 0; //set memory size to 0
		msName = asName; //input name is instance name

		mbUseMipMaps = false; //whether or not texture uses mipmaps
		mFilter = aFilter; // specified filter is texture filter
		mTextureType = aType; // specified type is texture filter
		mWrappingMode = aMode; // specified wrapping mode is texture wrapping mode

		// get around to this later
		mfAnisotropicFilteringDegree = 0.0f; // set anisotropic degree to 0
	}

	cTextureGL::~cTextureGL()
	{
		for (int i = 0; i < mvIDs.size(); ++i) // for every ID
		{
			glDeleteTextures(1, (GLuint*)&mvIDs[i]); //frees GPU memory held by each texture handle
		}
	}

	void cTextureGL::GenerateTextureIDs(int alNumToGen)
	{
		if (mvIDs.size() < alNumToGen) //not optimimal, but std::vector.resize() plays badly without this
		{
			int lNewTextures = alNumToGen - mvIDs.size(); //find the amount of new texture to be added to std::vector
			mvIDs.resize(alNumToGen); //resize the vector to size of textures to generate
			glGenTextures(alNumToGen, (GLuint*)&mvIDs[alNumToGen-lNewTextures]); //creates the texure handles sequentially
		}
	}

	bool cTextureGL::CreateTextureFromBitmap( cBitmap* apBitmap)
	{

		GenerateTextureIDs(1); //create 1 handle for the 1 image being used

		return CreateTextureFromBitmapIdx(apBitmap, 0); //create a texture from the specified bitmap
	}



	bool cTextureGL::CreateMipMaps()
	{
		glGenerateMipmap(GL_TEXTURE_2D); // UNUSED
		return true;
	}

	bool cTextureGL::CreateTextureFromBitmapIdx(cBitmap* apBitmap, int alIdx)
	{
		mbUseMipMaps = apBitmap->GetIsCompressed(); //not used currently, was a testing thing

		if (mTextureType == eTextureType_CubeMap)
		{
			// do nothing for now...
		}

		else
		{

			bool bRet = CreateTexture(mvIDs[alIdx], apBitmap->GetData(0, 0), apBitmap->GetNumberMipMaps(), apBitmap->GetDimensions(), apBitmap->GetBitmapFormat(), apBitmap->GetIsCompressed()); //forward the bitmap data to OpenGL

			//SetupTextureProperties(alIdx);

			return bRet; //returns whether the texure was created successfully or not
		}
		
		// setup the texture settings 
		//SetupTextureProperties(alIdx);

		return false;
	}

	

	bool cTextureGL::CreateTexture(int alID, cBitmapData* apBitmapData, int alNumberOfMipMaps, tVector3l avSize, eBitmapFormat aFormat, bool abIsCompressed)
	{
		GLenum Type = EnumToGLTextureType(mTextureType); // convert engine texture type to OpenGL texture type
		GLenum Format = EnumToGLPixelFormat(aFormat); // convert engine texture format to OpenGL texture format

		mvDimensions = avSize; // set the size of the texture

		glBindTexture(Type, alID); //let OpenGL know to set the current texture as active
		//glEnable(Type);

		bool bRet = true; // what we should return after looping
		tVector3l vResize = mvDimensions; //temp dimensions for loading mipmaps into openGL

	//	CopyTextureDataToGL(aFormat, 0, apBitmapData[0].mpData, apBitmapData[0].mlSize, vResize, abIsCompressed);

		for (int i = 0; i < alNumberOfMipMaps; ++i)
		{
			if (vResize.x == 0) vResize.x = 1; // texture Can't have side length 0, correct it if so!
			if (vResize.y == 0) vResize.y = 1;// texture Can't have side length 0, correct it if so!
			if (vResize.z == 0) vResize.z = 1;// texture Can't have side length 0, correct it if so!

			unsigned char* pData = apBitmapData[i].mpData; //gets the data of the bitmap
			size_t lSize = apBitmapData[i].mlSize; // gets the size in bytes of the data

			if (CopyTextureDataToGL(aFormat, i, pData,lSize,vResize, abIsCompressed) == false) // sends OpenGl the texure data per mip map specified. If data fails to be copied to OpenGL, stop loading
			{
				bRet = false; // return false
				break; //exit loop
			}

			vResize.x >>= 1;// shifts the dimensions by the nearest multiple of 2, for mip maps
			vResize.y >>= 1;// shifts the dimensions by the nearest multiple of 2, for mip maps
			vResize.z >>= 1;// shifts the dimensions by the nearest multiple of 2, for mip maps

		}
		if (bRet == false) return false; //actually return false if false

	//	glDisable(Type);
		
		SetupTextureProperties(alID); //setup the OpenGL properties of the texture

		return true;
	}

	bool cTextureGL::CopyTextureDataToGL(eBitmapFormat aFormat, int alMipMapLevel, unsigned char* apData, size_t alDataSize, tVector3l avSize, bool abIsCompressed)
	{
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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
				//Log("'%u'\n", glGetError());
			}
			else if (mTextureType == eTextureType_3D)
			{
				glTexImage3D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, avSize.z, 0, GL_UNSIGNED_BYTE, lFormat, apData);
			}
		}

		//glDisable(lType);

		 if (glGetError() != GL_NO_ERROR)
		 {
			 Error("Couldn't load Texture '%s'\n", msName.c_str());
			 return false;
		 }

		return true;
	}

	void cTextureGL::SetupTextureProperties(int alIdx)
	{
 		GLenum lType = EnumToGLTextureType(mTextureType);
		GLenum lWrapMode = EnumToGLTextureWrapMode(mWrappingMode);

		// test 
		//lWrapMode = GL_CLAMP_TO_EDGE;

		//glEnable(lType);
		glBindTexture(lType, alIdx);

		if (mbUseMipMaps && mTextureType != eTextureType_Rect)
		{
			if (mFilter != eTextureFilter_Bilinear)
				glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			else
				glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		}
		else {
			glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	
		glTexParameteri(lType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (mTextureType == eTextureType_Rect)
		{
			mWrappingMode = eTextureWrappingMode_ClampToEdge;
		}

		glTexParameteri(lType, GL_TEXTURE_WRAP_S, EnumToGLTextureWrapMode(mWrappingMode));
		glTexParameteri(lType, GL_TEXTURE_WRAP_T, EnumToGLTextureWrapMode(mWrappingMode));
		glTexParameteri(lType, GL_TEXTURE_WRAP_R, EnumToGLTextureWrapMode(mWrappingMode));

	//	glTexParameterf(lType, GL_TEXTURE_MAX_ANISOTROPY, 0.0f);

		//glDisable(lType);

	}


	void cTextureGL::Bind(int alUnit)
	{
		GLenum lType = EnumToGLTextureType(mTextureType);

		glActiveTexture(GL_TEXTURE0 + alUnit);

		glBindTexture(lType, mvIDs[0]);
		//glEnable(lType);
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