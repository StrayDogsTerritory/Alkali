#include "graphics/Bitmap.h"

#include "system/MemoryManager.h"
#include "system/SystemTypes.h"

#include <memory>

#include "engine/LogWriter.h"

namespace alk {

	int GetBytesPerPixel(eBitmapFormat aFormat)
	{
		switch (aFormat)
		{
		case eBitmapFormat_RGB: return 3;
		case eBitmapFormat_RGBA: return 4;
		case eBitmapFormat_Alpha: return 1;
		case eBitmapFormat_Luminance: return 1;
		}
	}


	cBitmapData::cBitmapData()
	{
		mlSize = 0;
		mpData = NULL;
	}

	cBitmapData::~cBitmapData()
	{
		if (mpData)
		{
			alkDeleteArray(mpData);
		}
	}

	void cBitmapData::SetData(size_t alSize, void* apData)
	{
		mlSize = alSize;
		mpData = alkNewArray(unsigned char, mlSize);

		memcpy(mpData, apData, mlSize);
	}

	cBitmap::cBitmap()
	{
		mvImages.resize(1);
		mvBitmapDimensions = 0;
		mlNumImages = 1;
		mlNumMipmaps = 1;
	}

	cBitmap::~cBitmap()
	{
		DeleteAll(mvImages);
	}


	cBitmapData* cBitmap::GetData(int alImage, int alMipmapLevel)
	{
		if (alImage < 0) return NULL;
		if (mlNumMipmaps <= alMipmapLevel) return NULL;

		return &mvImages[alImage * mlNumMipmaps + alMipmapLevel];
	}



	void cBitmap::SetUpData(int alImage, int alMipMap)
	{
		mlNumImages = alImage;
		mlNumMipmaps = alMipMap;
		mvImages.resize((size_t)(alImage * alMipMap));
	}

	bool cBitmap::CreateBitmap(tVector3l avDimensions, eBitmapFormat aBitmapFormat, int alImage, int alMipMap, void* apData)
	{
		mvBitmapDimensions = avDimensions;
		
		// normalize the bitmaps dimensions if needed
		if (mvBitmapDimensions.x <= 0) mvBitmapDimensions.x = 1;
		if (mvBitmapDimensions.y <= 0) mvBitmapDimensions.y = 1;
		if (mvBitmapDimensions.z <= 0) mvBitmapDimensions.z = 1;

		size_t lSize = mvBitmapDimensions.x * mvBitmapDimensions.y * mvBitmapDimensions.z  * GetBytesPerPixel(aBitmapFormat); 
 
		cBitmapData* pData = GetData(alImage, alMipMap);
		pData->mlSize = lSize;
		pData->mpData = apData;

		return true;
	}
	
}