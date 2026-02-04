#ifndef ALK_BITMAP_H
#define ALK_BITMAP_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <stdlib.h>
#include <vector>

namespace alk {

	class cBitmapData
	{
	public:
		cBitmapData();
		~cBitmapData();

		void SetData(size_t alSize, void* apData);

		size_t mlSize;
		void* mpData;
	};


	class cBitmap
	{
	public:
		cBitmap();
		~cBitmap();

		cBitmapData* GetData(int alImage, int alMipmapLevel);

		tVector3f GetSize() { return mvBitmapDimensions; }

		int GetLength() const { return mvBitmapDimensions.x; }
		int GetHeight() const { return mvBitmapDimensions.y; }
		int GetDepth() const { return mvBitmapDimensions.z; }

		bool CreateBitmap(tVector3f avDimensions,  size_t alSize, void* apData, bool abMipmaps, int alNumberMipMaps = 0);

	private:
		std::vector<cBitmapData*> mvImages;

		tVector3f mvBitmapDimensions;
		int mlNumImages;
		int mlNumMipmaps;
		size_t mlMemorySize;
	};

}

#endif
