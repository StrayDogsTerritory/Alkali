#ifndef ALK_BITMAP_H
#define ALK_BITMAP_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <stdlib.h>
#include <vector>

namespace alk {

	enum eBitmapFormat
	{
		eBitmapFormat_RGB,
		eBitmapFormat_RGBA,
		eBitmapFormat_Alpha,
		eBitmapFormat_BGR,
		eBitmapFormat_BGRA,
		eBitmapFormat_Luminance,
		eBitmapFormat_LuminanceAlpha,
		eBitmapCompressionFormat_DXT1,
		eBitmapCompressionFormat_DXT2,
		eBitmapCompressionFormat_DXT3,
		eBitmapCompressionFormat_DXT4,
		eBitmapCompressionFormat_DXT5,
		eBitmapCompressionFormat_3DC,
		eBitmapFormat_LastEnum
	};

	extern int GetBytesPerPixel(eBitmapFormat aFormat);

	class cBitmapData
	{
	public:
		cBitmapData();
		~cBitmapData();

		void SetData(size_t alSize, unsigned char* apData);

		size_t mlSize;
		unsigned char* mpData;
	};


	class cBitmap
	{
	public:
		cBitmap();
		~cBitmap();

		cBitmapData* GetData(int alImage, int alMipmapLevel);

		tVector3l GetDimensions() { return mvBitmapDimensions; }

		int GetLength() const { return mvBitmapDimensions.x; }
		int GetHeight() const { return mvBitmapDimensions.y; }
		int GetDepth() const { return mvBitmapDimensions.z; }

		int GetBytesPerPixel() const { return mlBytesPerPixel; }
		eBitmapFormat GetBitmapFormat() const { return mBitmapFormat; }

		bool GetIsCompressed() const { return mbCompressed; }

		void SetSize(tVector3l avSize) { mvBitmapDimensions = avSize; }
		void SetFormat(eBitmapFormat aFormat) { mBitmapFormat = aFormat; }
		void SetBytesPerPixel(int albbp) { mlBytesPerPixel = albbp; }
		void SetIsCompressed(bool abCompressed) { mbCompressed = abCompressed; }

		void SetUpData(int alImage, int alMipMap);

		bool CreateBitmap(tVector3l avDimensions, eBitmapFormat aBitmapFormat, int alImage, int alMipMap, unsigned char* apData);

	private:
		std::vector<cBitmapData> mvImages;

		bool mbCompressed;
		tVector3l mvBitmapDimensions;
		int mlNumImages;
		int mlNumMipmaps;
		eBitmapFormat mBitmapFormat;
		int mlBytesPerPixel;

	};

}

#endif
