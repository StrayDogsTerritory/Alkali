#include "resources/cSubLoader_BitmapDevIL_DDS.h"
#include "resources/DevILBitmapLoaderHelper.h"

#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

//#include <IL/il.h>

namespace alk {

	cSubLoader_BitmapDevIL_DDS::cSubLoader_BitmapDevIL_DDS()
	{
		AddExtension("dds");
		
	}

	cSubLoader_BitmapDevIL_DDS::~cSubLoader_BitmapDevIL_DDS()
	{

	}

	void cSubLoader_BitmapDevIL_DDS::SaveBitmap(cBitmap* apBitmap, const twString& asFile)
	{
		// make this work later
	//	return;
	}

	cBitmap* cSubLoader_BitmapDevIL_DDS::LoadBitmap(const twString& asFile)
	{
		ILuint lImageID;
		ilGenImages(1, (ILuint*)&lImageID);
		ilBindImage(lImageID);

		ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);

		if (!cDevILBitmapLoaderHelper::LoadBitmapDevIL(asFile))
		{
			Error("Couldn't load Bitmap '%s'!\n", cString::To8BitChar(asFile).c_str());
			ilDeleteImages(1, (ILuint*)&lImageID);
			return NULL;
		}

		cBitmap* pBitmap = alkNew(cBitmap, ());

		ILint lPixelFormat = ilGetInteger(IL_IMAGE_FORMAT);

		int lBytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		pBitmap->SetBytesPerPixel(lBytesPerPixel);

		int lCompressionFormat = ilGetInteger(IL_DXTC_DATA_FORMAT);

		int lNumImages = ilGetInteger(IL_NUM_IMAGES) + 1; // DevIL indexes images at 1. Fixes crashes.
		int lNumMipMaps = ilGetInteger(IL_NUM_MIPMAPS) + 1; // 1 because we consider the first image a mip map


		if (lNumImages > 1 || lNumMipMaps > 1)
			pBitmap->SetUpData(lNumImages, lNumMipMaps);

		tVector3l vDimensions;
		vDimensions.x = ilGetInteger(IL_IMAGE_WIDTH);
		vDimensions.y = ilGetInteger(IL_IMAGE_HEIGHT);
		vDimensions.z = ilGetInteger(IL_IMAGE_DEPTH);
		pBitmap->SetSize(vDimensions);

		if (lCompressionFormat != IL_DXT_NO_COMP)
		{
			pBitmap->SetIsCompressed(true);
			pBitmap->SetFormat(ILtoEnum(lCompressionFormat));

			for (int i = 0; i < (lNumImages > 0 ? lNumImages : 1); ++i)
				for (int m = 0; m < (lNumMipMaps > 0 ? lNumMipMaps : 1); ++m)
				{

					ilBindImage(lImageID);
					if (lNumImages > 1)	ilActiveImage(i);
					if (lNumMipMaps > 1) ilActiveMipmap(m);

					cBitmapData* pBitmapData = pBitmap->GetData(i, m);
					size_t lSize = (size_t)ilGetDXTCData(NULL, 0, lCompressionFormat);

					pBitmapData->mlSize = lSize;
					pBitmapData->mpData = alkNewArray(unsigned char, lSize);

					ilGetDXTCData(pBitmapData->mpData, pBitmapData->mlSize, lCompressionFormat);
				}

		}
		else
		{
			pBitmap->SetIsCompressed(false);
			pBitmap->SetFormat(ILtoEnum(lPixelFormat));

			for (int i = 0; i < (lNumImages > 0 ? lNumImages : 1); ++i)
				for (int m = 0; m < (lNumMipMaps > 0 ? lNumMipMaps : 1); ++m)
				{
					if (lNumImages > 1)
						ilActiveImage(i);
					if (lNumMipMaps > 1)
						ilActiveMipmap(m);

					cBitmapData* pBitmapData = pBitmap->GetData(i, m);

					size_t lSize = (size_t)ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
					pBitmapData->SetData(lSize, ilGetData());
				}
		}
		ilDeleteImages(1, (ILuint*)&lImageID);

		return pBitmap;
	}


	eBitmapFormat cSubLoader_BitmapDevIL_DDS::ILtoEnum(ILint aFormat)
	{
		switch (aFormat)
		{
		case IL_RGB: return eBitmapFormat_RGB;
		case IL_RGBA: return eBitmapFormat_RGBA;

		case IL_DXT1: return eBitmapCompressionFormat_DXT1;
		case IL_DXT2: return eBitmapCompressionFormat_DXT2;
		case IL_DXT3: return eBitmapCompressionFormat_DXT3;
		case IL_DXT4: return eBitmapCompressionFormat_DXT4;
		case IL_DXT5: return eBitmapCompressionFormat_DXT5;
		case IL_3DC: return eBitmapCompressionFormat_3DC;

		default: return eBitmapFormat_LastEnum;
		}
	}
}