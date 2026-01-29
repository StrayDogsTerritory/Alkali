#ifndef ALK_BITMAP_H
#define ALK_BITMAP_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

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

		bool CreateBitmap();

		tVector3l GetSize() { return mvBitmapDimensions; }

		int GetLength() { return mvBitmapDimensions.x; }
		int GetHeight() { return mvBitmapDimensions.y; }
		int GetDepth() { return mvBitmapDimensions.z; }


	private:
		std::vector<cBitmapData*> mvImages;

		tVector3l mvBitmapDimensions;
		int mlNumImages;
	};

}

#endif
