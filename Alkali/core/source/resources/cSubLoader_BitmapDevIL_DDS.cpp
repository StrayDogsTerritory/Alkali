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

		if (!cDevILBitmapLoaderHelper::LoadBitmapDevIL(asFile))
		{
			Error("Couldn't load Bitmap '%s'!\n", cString::To8BitChar(asFile).c_str());
			ilDeleteImages(1, (ILuint*)&lImageID);
			return NULL;
		}

		cBitmap* pBitmap = alkNew(cBitmap, ());

		int lBytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		pBitmap->SetBytesPerPixel(lBytesPerPixel);

		ILint lPixelFormat = ilGetInteger(IL_IMAGE_FORMAT);
		pBitmap->SetFormat(ILtoEnum(lPixelFormat));

		int lCompressionFormat = ilGetInteger(IL_DXTC_DATA_FORMAT);

		int lNumImages = ilGetInteger(IL_NUM_IMAGES);
		int lNumMipMaps = ilGetInteger(IL_NUM_MIPMAPS) + 1; // 1 because we consider the first image a mip map


		if (lNumImages > 1)
			pBitmap->SetUpData(lNumImages, lNumMipMaps);

		tVector3l vDimensions;
		vDimensions.x = ilGetInteger(IL_IMAGE_WIDTH);
		vDimensions.y = ilGetInteger(IL_IMAGE_HEIGHT);
		vDimensions.z = ilGetInteger(IL_IMAGE_DEPTH);
		pBitmap->SetSize(vDimensions);

		Log("Bitmap Properties:\n");
		Log("Bitmap Dimensions: %s\n", vDimensions.ToString().c_str());
		Log("Bitmap Format: %d\n", lPixelFormat);
		Log("Bitmap Bytes per pixel: %d\n", lBytesPerPixel);
		Log("Bitmap Images: %d\n", lNumImages);
		Log("Bitmap Mip maps: %d\n", lNumMipMaps);
		Log("Bitmap Compression: %d\n", lCompressionFormat != IL_DXT_NO_COMP);

		// if the bitmap has mipmaps, load it differently
		int lCount = lNumImages > 0 ? lNumImages : 1;
		for (int i = 0; i < lCount; ++i)
		for (int m = 0; m < lCount; ++m)
		{
			if (lNumImages > 1)
				ilActiveImage(i);
			if (lNumMipMaps > 1)
				ilActiveMipmap(m);

			cBitmapData* pBitmapData = pBitmap->GetData(i, m);

			size_t lSize = (size_t)ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
			pBitmapData->SetData(lSize, ilGetData());
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

		default: return eBitmapFormat_LastEnum;
		}
	}
}