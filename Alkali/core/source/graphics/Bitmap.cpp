#include "graphics/Bitmap.h"

#include "system/MemoryManager.h"
#include "system/SystemTypes.h"

#include <memory>

#include "engine/LogWriter.h"

namespace alk {

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
		mlMemorySize = 0;
	}

	cBitmap::~cBitmap()
	{
		DeleteAll(mvImages);
	}


	cBitmapData* cBitmap::GetData(int alImage, int alMipmapLevel)
	{
		if (alImage < 0) return NULL;
		if (mlNumMipmaps <= alMipmapLevel) return NULL;

		return mvImages[alImage * mlNumMipmaps + alMipmapLevel];
	}



	bool cBitmap::CreateBitmap(tVector3f avDimensions, size_t alSize, void* apData, bool abMipmaps, int alNumberMipMaps)
	{
		mvBitmapDimensions = avDimensions;
		
		// normalize the bitmaps dimensions
		if (mvBitmapDimensions.x <= 0) mvBitmapDimensions.x = 1;
		if (mvBitmapDimensions.y <= 0) mvBitmapDimensions.y = 1;
		if (mvBitmapDimensions.z <= 0) mvBitmapDimensions.z = 1;

		size_t lSize = mvBitmapDimensions.x * mvBitmapDimensions.y * mvBitmapDimensions.z; // * GetBytesPerPixel(aFormat); set this up later
 
		cBitmapData* pData = GetData(alImage, alNumberMipMaps);
		pData->SetData(lSize, apData);

		return true;
	}
}