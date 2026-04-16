#include "resources/SubLoader_BitmapDevIL.h"
#include "resources/DevILBitmapLoaderHelper.h"

#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

//#include <IL/il.h>

namespace alk {

	cSubLoader_BitmapDevIL::cSubLoader_BitmapDevIL()
	{
		// add support for these extensions
		AddExtension("png"); 
		AddExtension("jpg");
		AddExtension("jpeg");
		AddExtension("tga");
	}

	//-------------------------------------------------------------------------------------

	cSubLoader_BitmapDevIL::~cSubLoader_BitmapDevIL()
	{
		// does nothing
	}

	//-------------------------------------------------------------------------------------

	void cSubLoader_BitmapDevIL::SaveBitmap(cBitmap* apBitmap, const twString& asFile)
	{
		// make this work later it's like a whole thing that I couldn't get around to...
	//	return;
	}

	//-------------------------------------------------------------------------------------

	cBitmap* cSubLoader_BitmapDevIL::LoadBitmap(const twString& asFile)
	{
		/*
		* fun note, a lot of this code is structured like OpenGl despite being made by different groups
		*/
		ILuint lImageID; // create an ID for the image being loaded (only 1 image, seperate loader for multi-image formats like DDS)
		ilGenImages(1, (ILuint*)&lImageID); // generate the ID
		ilBindImage(lImageID); // tell DevIL to activate the image

		if (!cDevILBitmapLoaderHelper::LoadBitmapDevIL(asFile)) //if we can't load the bitmap...
		{
			Error("Couldn't load Bitmap '%s'!\n",cString::To8BitChar(asFile).c_str()); // let the user know 
			ilDeleteImages(1, (ILuint*)&lImageID); // delete the image
			return NULL;
		}

		cBitmap* pBitmap = alkNew(cBitmap, ()); // create a bitmap

		int lBytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); // get bbp
		pBitmap->SetBytesPerPixel(lBytesPerPixel); //set bbp

		ILint lPixelFormat = ilGetInteger(IL_IMAGE_FORMAT); // get format
		pBitmap->SetFormat(ILtoEnum(lPixelFormat)); //convert, set format

		int lNumImages = ilGetInteger(IL_NUM_IMAGES); // get num images
		int lNumMipMaps = ilGetInteger(IL_NUM_MIPMAPS) + 1; // get nums of mip maps +1 because we consider the first image a mip map

		if (lNumImages > 1) // if more than 0 images
			pBitmap->SetUpData(lNumImages, lNumMipMaps); // create the data in the bitmap

		tVector3l vDimensions; //temp dims
		vDimensions.x = ilGetInteger(IL_IMAGE_WIDTH); //get x
		vDimensions.y = ilGetInteger(IL_IMAGE_HEIGHT);//get y
		vDimensions.z = ilGetInteger(IL_IMAGE_DEPTH);//get z
		pBitmap->SetSize(vDimensions); // set the size

		// if the bitmap has mipmaps, load it differently
		int lCount = lNumImages > 0 ? lNumImages : 1; // code shared between other sub loader for DDS images, so this doesn't really do much of anything
		for (int i = 0; i < lCount; ++i)
		{
			if (lNumImages > 1)
				ilActiveImage(i); // activiate image
			
			cBitmapData* pBitmapData = pBitmap->GetData(i, 0); // retrive the empty value of vector

			size_t lSize = (size_t)ilGetInteger(IL_IMAGE_SIZE_OF_DATA); // set data size
			pBitmapData->SetData(lSize, ilGetData()); // set the data
		}

		ilDeleteImages(1, (ILuint*)&lImageID); // now that we're done, release the IDs

		return pBitmap;
	}

	//-------------------------------------------------------------------------------------

	eBitmapFormat cSubLoader_BitmapDevIL::ILtoEnum(ILint aFormat)
	{
		switch (aFormat) //converts, just a LUT so I won't bother explaining it line-by-line
		{
		case IL_RGB: return eBitmapFormat_RGB;
		case IL_RGBA: return eBitmapFormat_RGBA;

		default: return eBitmapFormat_LastEnum;
		}
	}

	//-------------------------------------------------------------------------------------
}