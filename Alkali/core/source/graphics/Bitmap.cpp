#include "graphics/Bitmap.h"

#include "system/MemoryManager.h"

#include <memory>

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
	}
}