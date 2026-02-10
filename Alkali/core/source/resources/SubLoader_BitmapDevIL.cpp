#include "resources/SubLoader_BitmapDevIL.h"
#include "resources/DevILBitmapLoaderHelper.h"

#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

#include <IL/il.h>

namespace alk {

	cSubLoader_BitmapDevIL::cSubLoader_BitmapDevIL()
	{
		AddExtension("png");
	}

	cSubLoader_BitmapDevIL::~cSubLoader_BitmapDevIL()
	{

	}

	void cSubLoader_BitmapDevIL::SaveBitmap(cBitmap* apBitmap, const twString& asFile)
	{
		// make this work later
	//	return;
	}

	cBitmap* cSubLoader_BitmapDevIL::LoadBitmap(const twString& asFile)
	{
		ILuint lImageID;
		ilGenImages(1, (ILuint*)&lImageID);
		ilBindImage(lImageID);

		if (!cDevILBitmapLoaderHelper::LoadBitmapDevIL(asFile))
		{
			Error("Couldn't load Bitmap '%s'!\n",cString::To8BitChar(asFile).c_str());
			ilDeleteImages(1, (ILuint*)&lImageID);
			return NULL;
		}

		cBitmap* pBitmap = alkNew(cBitmap, ());

		int lNumImages = ilGetInteger(IL_NUM_IMAGES);
		int lNumMipMaps = ilGetInteger(IL_NUM_MIPMAPS);

		pBitmap->SetUpData(lNumImages, lNumMipMaps);

		tVector3l vDimensions;
		vDimensions.x = ilGetInteger(IL_IMAGE_WIDTH);
		vDimensions.y = ilGetInteger(IL_IMAGE_HEIGHT);
		vDimensions.z = ilGetInteger(IL_IMAGE_DEPTH);
		pBitmap->SetSize(vDimensions);

		// if the bitmap has mipmaps, load it differently
		if (lNumImages < 1)
		{
			for (int i = 0; i < lNumImages; ++i)
			{
				ilActiveImage(i);

				cBitmapData* pBitmapData = pBitmap->GetData(i, 0);

				size_t lSize = (size_t)ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
				pBitmapData->SetData(lSize, ilGetData());
			}
		}
		else
		{
			
		}

		ilDeleteImages(1, (ILuint*)&lImageID);

		return pBitmap;
	}
}