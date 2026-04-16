#include "graphics/Bitmap.h"

#include "system/MemoryManager.h"
#include "system/SystemTypes.h"

#include <memory>

#include "engine/LogWriter.h"

namespace alk {

	//-------------------------------------------------------------------------------------

	int GetBytesPerPixel(eBitmapFormat aFormat) // how many bytes per pixel
	{
		switch (aFormat)
		{
		case eBitmapFormat_RGB: return 3;
		case eBitmapFormat_RGBA: return 4;
		case eBitmapFormat_Alpha: return 1;
		case eBitmapFormat_Luminance: return 1;
		}
	}

	//-------------------------------------------------------------------------------------

	cBitmapData::cBitmapData()
	{
		mlSize = 0; //setup the size of the data
		mpData = NULL; // no data, make it null
	}

	//-------------------------------------------------------------------------------------

	cBitmapData::~cBitmapData()
	{
		if (mpData) //if data non null
		{
			alkDeleteArray(mpData); // delete the byte array
		}
	}

	//-------------------------------------------------------------------------------------

	void cBitmapData::SetData(size_t alSize, unsigned char* apData)
	{
		mlSize = alSize; // size is as specified
		mpData = alkNewArray(unsigned char, mlSize); //create an array of unsigned chars of mlSize

		memcpy(mpData, apData, mlSize); //copy the input pixel data into the array
	}

	//-------------------------------------------------------------------------------------

	cBitmap::cBitmap()
	{
		mvImages.resize(1); //always 1 image
		mvBitmapDimensions = 0; //no dims
		mlNumImages = 1; // 1 image
		mlNumMipmaps = 1; // 1 mipmap (the og image)
		mlBytesPerPixel = 0; // no bpp
		mBitmapFormat = eBitmapFormat_LastEnum; // no format
		mbCompressed = false; // not compressed
	}

	//-------------------------------------------------------------------------------------

	cBitmap::~cBitmap()
	{
		//DeleteAll(mvImages);
		// does nothing
	}

	//-------------------------------------------------------------------------------------

	cBitmapData* cBitmap::GetData(int alImage, int alMipmapLevel)
	{
		if (alImage < 0) return NULL; // if there's negative images... something's gone wrong, return NULL
		if (mlNumMipmaps <= alMipmapLevel) return NULL; // if there's less mipmaps than we're indexing by, something is wrong, return NULL

		return &mvImages[(size_t)(alImage * mlNumMipmaps + alMipmapLevel)]; // get the pointer at the index of the image * the amount of mipmaps in the bitmap + the level we're indexing to
	}

	//-------------------------------------------------------------------------------------

	void cBitmap::SetUpData(int alImage, int alMipMap)
	{
		mlNumImages = alImage; //amount of images = input
		mlNumMipmaps = alMipMap; // amount of mipmaps = input
		mvImages.resize((size_t)(alImage * alMipMap)); //resize the vector to the specified amount of images * bitmaps
	}

	//-------------------------------------------------------------------------------------

	bool cBitmap::CreateBitmap(tVector3l avDimensions, eBitmapFormat aBitmapFormat, int alImage, int alMipMap, unsigned char* apData)
	{
		mvBitmapDimensions = avDimensions; //dims = input
		
		// normalize the bitmaps dimensions if needed
		if (mvBitmapDimensions.x <= 0) mvBitmapDimensions.x = 1;// if the dims are 0, set them to 1
		if (mvBitmapDimensions.y <= 0) mvBitmapDimensions.y = 1;// if the dims are 0, set them to 1
		if (mvBitmapDimensions.z <= 0) mvBitmapDimensions.z = 1;// if the dims are 0, set them to 1

		size_t lSize = (size_t)(mvBitmapDimensions.x * mvBitmapDimensions.y * mvBitmapDimensions.z  * GetBytesPerPixel()); // data size is dims * bpp
 
		cBitmapData* pData = GetData(alImage, alMipMap); //get the data in the vector (requres that the data has already been setup
		pData->SetData(lSize, apData); //set the specified data to input data

		return true;
	}
	
	//-------------------------------------------------------------------------------------

}