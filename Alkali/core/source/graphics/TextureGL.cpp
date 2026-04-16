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

	//-------------------------------------------------------------------------------------

	cTextureGL::~cTextureGL()
	{
		for (int i = 0; i < mvIDs.size(); ++i) // for every ID
		{
			glDeleteTextures(1, (GLuint*)&mvIDs[i]); //frees GPU memory held by each texture handle
		}
	}

	//-------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------

	bool cTextureGL::CreateMipMaps()
	{
		glGenerateMipmap(GL_TEXTURE_2D); // UNUSED
		return true;
	}

	//-------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------

	bool cTextureGL::CopyTextureDataToGL(eBitmapFormat aFormat, int alMipMapLevel, unsigned char* apData, size_t alDataSize, tVector3l avSize, bool abIsCompressed)
	{
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // temp crash fixer

		GLenum lType = EnumToGLTextureType(mTextureType); // convert engine texture type to OpenGL texture type
		GLenum lFormat = EnumToGLPixelFormat(aFormat); // convert engine texture format to OpenGL texture type

		while (glGetError() != GL_NO_ERROR); // clear the error log to make error testing feasable

		mlMemorySize += alDataSize; // set memory size of texture to that of the bitmaps

		if (abIsCompressed) // if the texture is compressed, needs to be loaded differently
		{
			if (mTextureType == eTextureType_1D) // 1D texture
			{
				glCompressedTexImage1D(lType, alMipMapLevel, lFormat, avSize.x,0, alDataSize, apData); // finally, we get to actually load data into the texture buffer
			}
			else if (mTextureType == eTextureType_2D || mTextureType == eTextureType_CubeMap || mTextureType == eTextureType_Rect)
			{
				glCompressedTexImage2D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, 0, alDataSize, apData);// finally, we get to actually load data into the texture buffer
			}
			else if (mTextureType == eTextureType_3D)
			{
				glCompressedTexImage3D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, avSize.z, 0, alDataSize, apData);// finally, we get to actually load data into the texture buffer
			}
		}
		else // little different load, needs to specify bitmap format, in this case, all unsigned byte
		{
			if (mTextureType == eTextureType_1D)
			{
				glTexImage1D(lType, alMipMapLevel, lFormat, avSize.x, 0, lFormat, GL_UNSIGNED_BYTE, apData);// finally, we get to actually load data into the texture buffer
			}
			else if (mTextureType == eTextureType_2D || mTextureType == eTextureType_CubeMap || mTextureType == eTextureType_Rect)
			{
				glTexImage2D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, 0, lFormat, GL_UNSIGNED_BYTE, apData);// finally, we get to actually load data into the texture buffer
				//Log("'%u'\n", glGetError());
			}
			else if (mTextureType == eTextureType_3D)
			{
				glTexImage3D(lType, alMipMapLevel, lFormat, avSize.x, avSize.y, avSize.z, 0, GL_UNSIGNED_BYTE, lFormat, apData);// finally, we get to actually load data into the texture buffer
			}
		}

		//glDisable(lType);

		 if (glGetError() != GL_NO_ERROR) // if there's an error
		 {
			 Error("Couldn't load Texture '%s'\n", msName.c_str());// tell the user the load failed
			 return false;
		 }

		return true;
	}

	//-------------------------------------------------------------------------------------

	void cTextureGL::SetupTextureProperties(int alIdx)
	{
 		GLenum lType = EnumToGLTextureType(mTextureType);// convert engine texture type to OpenGL texture type
		GLenum lWrapMode = EnumToGLTextureWrapMode(mWrappingMode);// convert engine texture wrap mode to OpenGL texture type

		// test 
		//lWrapMode = GL_CLAMP_TO_EDGE;

		//glEnable(lType);
		glBindTexture(lType, alIdx);//let OpenGL know to set the current texture as active

		if (mbUseMipMaps && mTextureType != eTextureType_Rect) // if we use mipmaps use bilinear/trilinear filtering
		{
			if (mFilter != eTextureFilter_Bilinear) //trilinear filting
				glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			else// bilinear filtering
				glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		}
		else { //otherwise use linear filtering
			glTexParameteri(lType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	
		glTexParameteri(lType, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // magnifying is always linear

		if (mTextureType == eTextureType_Rect) // rectangle texture can only be clamp to edge
		{
			mWrappingMode = eTextureWrappingMode_ClampToEdge;
		}

		glTexParameteri(lType, GL_TEXTURE_WRAP_S, EnumToGLTextureWrapMode(mWrappingMode)); //set the wrap mode
		glTexParameteri(lType, GL_TEXTURE_WRAP_T, EnumToGLTextureWrapMode(mWrappingMode));//set the wrap mode
		glTexParameteri(lType, GL_TEXTURE_WRAP_R, EnumToGLTextureWrapMode(mWrappingMode));//set the wrap mode

	//	glTexParameterf(lType, GL_TEXTURE_MAX_ANISOTROPY, 0.0f);

		//glDisable(lType);

	}

	//-------------------------------------------------------------------------------------

	void cTextureGL::Bind(int alUnit)
	{
		GLenum lType = EnumToGLTextureType(mTextureType);// convert engine texture type to OpenGL texture type

		glActiveTexture(GL_TEXTURE0 + alUnit); //tell OGL to activate the texture, + the texture unit we want (only 1 unit supported currently)

		glBindTexture(lType, mvIDs[0]); //binds the texture (only the 0th ID for now)
		//glEnable(lType);
	}

	//-------------------------------------------------------------------------------------

	/*
	* no comments for each of these, just converts engine formats into OpenGL formats and vice versa
	*/

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

	//-------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------

	GLenum cTextureGL::EnumToGLTextureFilter(eTextureFilter aTextureFilter)
	{
		switch (aTextureFilter)
		{
		case eTextureFilter_Bilinear: return GL_LINEAR;
		case eTextureFilter_Trilinear: return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	//-------------------------------------------------------------------------------------
}