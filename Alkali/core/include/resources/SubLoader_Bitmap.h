#ifndef ALK_SUBLOADERBITMAP_H
#define ALK_SUBLOADERBITMAP_H

#include "resources/SubLoader.h"

#include "graphics/Bitmap.h"

/*
* Created by Simon Stroomer
* Sub loader class for the bitmap, though this one also has to be abstract so that I can use a library to load bitmaps
*/

namespace alk {

	class iSubloader_Bitmap : public iSubLoader
	{
	public:

		//-------------------------------------------------------------------------------------

		iSubloader_Bitmap() {} //constructor
		virtual ~iSubloader_Bitmap() {} // destructor

		//-------------------------------------------------------------------------------------

		virtual void SaveBitmap(cBitmap* apBitmap, const twString& asFile)=0; //saves bitmaps: currently unused
		virtual cBitmap* LoadBitmap(const twString& asFile)=0; // Loads bitmaps

		//-------------------------------------------------------------------------------------
	};
}

#endif
