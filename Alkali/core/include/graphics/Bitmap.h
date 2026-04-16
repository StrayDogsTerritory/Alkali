#ifndef ALK_BITMAP_H
#define ALK_BITMAP_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <stdlib.h>
#include <vector>

/*
* Created by Simon Stroomer
* 
* Class that can hold bitmap data of a speccific format for textures or other engine applications of images.
*/

namespace alk {


	enum eBitmapFormat// supported bitmap formats enum
	{
		eBitmapFormat_RGB,
		eBitmapFormat_RGBA,
		eBitmapFormat_Alpha,
		eBitmapFormat_BGR,
		eBitmapFormat_BGRA,
		eBitmapFormat_Luminance, //black and white image, no colour data
		eBitmapFormat_LuminanceAlpha, // same as before but with alpha
		// compressed formats
		eBitmapCompressionFormat_DXT1,
		eBitmapCompressionFormat_DXT2,
		eBitmapCompressionFormat_DXT3,
		eBitmapCompressionFormat_DXT4,
		eBitmapCompressionFormat_DXT5,
		eBitmapCompressionFormat_3DC,
		eBitmapFormat_LastEnum
	};

	extern int GetBytesPerPixel(eBitmapFormat aFormat); //extern so texture classes can call this without issue

	class cBitmapData
	{
	public:

		cBitmapData(); //constructor
		~cBitmapData(); //destructor
		//-------------------------------------------------------------------------------------

		void SetData(size_t alSize, unsigned char* apData); //set specified bitmap data

		//-------------------------------------------------------------------------------------

		size_t mlSize; //size of data
		unsigned char* mpData; //raw data
	};


	class cBitmap
	{
	public:
		cBitmap(); //constructor
		~cBitmap(); // destructor

		//-------------------------------------------------------------------------------------

		cBitmapData* GetData(int alImage, int alMipmapLevel); //gets specific data from the std::vector

		//-------------------------------------------------------------------------------------

		tVector3l GetDimensions() { return mvBitmapDimensions; } // gets dimension vector of the bitmap

		//-------------------------------------------------------------------------------------

		int GetLength() const { return mvBitmapDimensions.x; } // gets the x size of the bitmap
		int GetHeight() const { return mvBitmapDimensions.y; }// gets the y size of the bitmap
		int GetDepth() const { return mvBitmapDimensions.z; }// gets the z size of the bitmap

		//-------------------------------------------------------------------------------------

		int GetNumberMipMaps() const { return mlNumMipmaps; } //gets the amount of mipmaps in the image

		//-------------------------------------------------------------------------------------

		int GetNumberImages() const { return mlNumImages; } //gets how many differenct images are in the bitmap (including mip maps)

		//-------------------------------------------------------------------------------------

		int GetBytesPerPixel() const { return mlBytesPerPixel; } //get the bpp of the image

		//-------------------------------------------------------------------------------------

		eBitmapFormat GetBitmapFormat() const { return mBitmapFormat; } // get the format of the bitmap

		//-------------------------------------------------------------------------------------

		bool GetIsCompressed() const { return mbCompressed; } // is the bitmap compressed?

		//-------------------------------------------------------------------------------------

		void SetSize(tVector3l avSize) { mvBitmapDimensions = avSize; } // set the size of the bitmap

		//-------------------------------------------------------------------------------------
		
		void SetFormat(eBitmapFormat aFormat) { mBitmapFormat = aFormat; } // set the format of the bitmap

		//-------------------------------------------------------------------------------------
		
		void SetBytesPerPixel(int albbp) { mlBytesPerPixel = albbp; }// set the bpp of the bitmap
		
		//-------------------------------------------------------------------------------------

		void SetIsCompressed(bool abCompressed) { mbCompressed = abCompressed; }// set if the bitmap is compressed

		//-------------------------------------------------------------------------------------

		void SetUpData(int alImage, int alMipMap); // set up the data

		//-------------------------------------------------------------------------------------

		bool CreateBitmap(tVector3l avDimensions, eBitmapFormat aBitmapFormat, int alImage, int alMipMap, unsigned char* apData); // create a bitmap

		//-------------------------------------------------------------------------------------

	private:
		std::vector<cBitmapData> mvImages; // amount of mipmaps and images in bitmap

		bool mbCompressed; //is compressed
		tVector3l mvBitmapDimensions; //dims
		int mlNumImages; //num images
		int mlNumMipmaps; // num mipmaps
		eBitmapFormat mBitmapFormat; //bitmap format
		int mlBytesPerPixel; // bpp

	};

}

#endif
