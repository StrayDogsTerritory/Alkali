#ifndef ALK_SUBLOADERBITMAPDEVIL_H
#define ALK_SUBLOADERBITMAPDEVIL_H

#include "resources/SubLoader_Bitmap.h"

#include <IL/il.h>

/*
* Created by Simon Stroomer
* loads non DDS images while using DevIL to do the hard parts
*/

namespace alk {

	class cSubLoader_BitmapDevIL : public iSubloader_Bitmap
	{
		
	public:
	//	friend class cDevILBitmapLoaderHandler;
		//-------------------------------------------------------------------------------------

		cSubLoader_BitmapDevIL(); // constructor
		~cSubLoader_BitmapDevIL(); // destructor

		//-------------------------------------------------------------------------------------

		 void SaveBitmap(cBitmap* apBitmap,const twString& asFile); // UNUSED: saves the bitmap
		 cBitmap* LoadBitmap(const twString& asFile);// Loads bitmap from disk

		 //-------------------------------------------------------------------------------------

	private:
		 eBitmapFormat ILtoEnum(ILint aFormat); // convert DevIL enums to engine enums
	};
}

#endif
