#ifndef ALK_DEVILBITMAPLAODERHELPER_H
#define ALK_DEVILBITMAPLOADERHELPER_H

#include "system/String.h"

#include <IL/il.h>

/*
* Created by Simon Stroomer
* couple of helper functions for loading and I guess saving (never finished it)
*/

namespace alk {

	class cBitmap;

	class cDevILBitmapLoaderHelper
	{
	public:
		//-------------------------------------------------------------------------------------

		static bool SaveBitmapDevIL(cBitmap* apBitmap, const twString& asFile); // saves a file to disk with DevIL
		static bool LoadBitmapDevIL(const twString& asFile); // loads a file to disk with DevIL

		//-------------------------------------------------------------------------------------
	private:

		//-------------------------------------------------------------------------------------

		static ILint GetILFormatFromExt(const tString& asName); // file ext to DevIL ext conversion

		//-------------------------------------------------------------------------------------

	};

}

#endif
