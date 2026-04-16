#include "resources/cSubLoader_BitmapDevIL_DDS.h"
#include "resources/DevILBitmapLoaderHelper.h"

#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

//#include <IL/il.h>

namespace alk {

	cSubLoader_BitmapDevIL_DDS::cSubLoader_BitmapDevIL_DDS()
	{
		// add support for dds
		AddExtension("dds");
		
	}

	//-------------------------------------------------------------------------------------

	cSubLoader_BitmapDevIL_DDS::~cSubLoader_BitmapDevIL_DDS()
	{
		// does nothing
	}

	//-------------------------------------------------------------------------------------

	void cSubLoader_BitmapDevIL_DDS::SaveBitmap(cBitmap* apBitmap, const twString& asFile)
	{
		// make this work later
	//	return;
	}

	//-------------------------------------------------------------------------------------

	cBitmap* cSubLoader_BitmapDevIL_DDS::LoadBitmap(const twString& asFile)
	{
		/*
			* fun note, a lot of this code is structured like OpenGl despite being made by different groups
			*/
		ILuint lImageID; // create an ID for the image being loaded (only 1 image, seperate loader for multi-image formats like DDS)
		ilGenImages(1, (ILuint*)&lImageID); // generate the ID
		ilBindImage(lImageID); // tell DevIL to activate the image

		if (!cDevILBitmapLoaderHelper::LoadBitmapDevIL(asFile)) //if we can't load the bitmap...
		{
			Error("Couldn't load Bitmap '%s'!\n", cString::To8BitChar(asFile).c_str()); // let the user know 
			ilDeleteImages(1, (ILuint*)&lImageID); // delete the image
			return NULL;
		}

		cBitmap* pBitmap = alkNew(cBitmap, ()); // create a bitmap

		int lBytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); // get bbp
		pBitmap->SetBytesPerPixel(lBytesPerPixel); //set bbp

		ILint lPixelFormat = ilGetInteger(IL_IMAGE_FORMAT); // get format
		pBitmap->SetFormat(ILtoEnum(lPixelFormat)); //convert, set format

		int lCompressionFormat = ilGetInteger(IL_DXTC_DATA_FORMAT);

		int lNumImages = ilGetInteger(IL_NUM_IMAGES); // get num images
		int lNumMipMaps = ilGetInteger(IL_NUM_MIPMAPS) + 1; // get nums of mip maps +1 because we consider the first image a mip map

		if (lNumImages > 1) // if more than 0 images
			pBitmap->SetUpData(lNumImages, lNumMipMaps); // create the data in the bitmap

		tVector3l vDimensions; //temp dims
		vDimensions.x = ilGetInteger(IL_IMAGE_WIDTH); //get x
		vDimensions.y = ilGetInteger(IL_IMAGE_HEIGHT);//get y
		vDimensions.z = ilGetInteger(IL_IMAGE_DEPTH);//get z
		pBitmap->SetSize(vDimensions); // set the size

		if (lCompressionFormat != IL_DXT_NO_COMP) // if compressed
		{
			pBitmap->SetIsCompressed(true); // set compressed
			pBitmap->SetFormat(ILtoEnum(lCompressionFormat)); // set the compressed format

			for (int i = 0; i < lNumImages; ++i) // for every image
				for (int m = 0; m < lNumMipMaps; ++m) // for every mipmap of i images
				{

					ilBindImage(lImageID); // bind image
					if (lNumImages > 1)	ilActiveImage(i); //activate image
					if (lNumMipMaps > 1) ilActiveMipmap(m);//activate mip maps

					cBitmapData* pBitmapData = pBitmap->GetData(i, m); // get empty value at i and m of std::vector
					size_t lSize = (size_t)ilGetDXTCData(NULL, 0, lCompressionFormat); // get the size of compressed data

					pBitmapData->mlSize = lSize; // set size
					pBitmapData->mpData = alkNewArray(unsigned char, lSize); // create the data 

					ilGetDXTCData(pBitmapData->mpData, pBitmapData->mlSize, lCompressionFormat); // add the data to the bitmap
				}

		}
		else // uncompressed
		{
			pBitmap->SetIsCompressed(false); // set not compressed
			pBitmap->SetFormat(ILtoEnum(lPixelFormat)); //set format

			for (int i = 0; i < (lNumImages > 0 ? lNumImages : 1); ++i) // for every image
				for (int m = 0; m < (lNumMipMaps > 0 ? lNumMipMaps : 1); ++m) // for every mip map
				{
					ilBindImage(lImageID); // bind active
					if (lNumImages > 1) ilActiveImage(i); // activate image
					if (lNumMipMaps > 1) ilActiveMipmap(m); // activate mip map

					cBitmapData* pBitmapData = pBitmap->GetData(i, m); // get empty value at i and m of std::vector

					size_t lSize = (size_t)ilGetInteger(IL_IMAGE_SIZE_OF_DATA); // get size of data
					pBitmapData->SetData(lSize, ilGetData()); // add data to the bitmap
				}
		}
		ilDeleteImages(1, (ILuint*)&lImageID); // finally release the IDs 
		/// fun fact, this is the 300th comment I've written today! How many words do you think that is? 100? 1000 even?

		return pBitmap;
	}

	//-------------------------------------------------------------------------------------

	eBitmapFormat cSubLoader_BitmapDevIL_DDS::ILtoEnum(ILint aFormat)
	{
		switch (aFormat)//converts, just a LUT so I won't bother explaining it line-by-line
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

	//-------------------------------------------------------------------------------------
}