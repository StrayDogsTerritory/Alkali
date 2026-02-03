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
		mlMipMapLevels = 0;
		mlMemorySize = 0;
	}

	cBitmap::~cBitmap()
	{
		DeleteAll(mvImages);
	}


	cBitmapData* cBitmap::GetData( int alImage, int alMipmapLevel)
	{
		if (alImage < 0) return NULL;
		if (mlMipMapLevels < alMipmapLevel) return NULL;

		return mvImages[alImage + alMipmapLevel];
	}



	bool cBitmap::CreateBitmap(tVector3f avDimensions, size_t alSize, void* apData, bool abMipmaps, int alNumberMipMaps)
	{
		mvBitmapDimensions = avDimensions;
		
		cBitmapData* pBitmapData = alkNew(cBitmapData, ());
		pBitmapData->SetData(alSize, apData);
		mvImages.push_back(pBitmapData);

		// support mipmaps later
		if (abMipmaps || alNumberMipMaps > 0)
		{
			Error("Mipmapping is not supported! Do not use!\n");
			return false;
		}

		return true;
	}
}