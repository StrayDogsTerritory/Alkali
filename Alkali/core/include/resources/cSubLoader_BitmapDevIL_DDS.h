#ifndef ALK_SUBLOADERBITMAPDEVILDDS_H
#define ALK_SUBLOADERBITMAPDEVILDDS_H
#include "resources/SubLoader_Bitmap.h"

#include <IL/il.h>

/*
* Created by Simon Stroomer
* loads DDS images while using DevIL to do the hard parts
*/

	namespace alk {

		class cSubLoader_BitmapDevIL_DDS : public iSubloader_Bitmap
		{
		public:

			//-------------------------------------------------------------------------------------

			cSubLoader_BitmapDevIL_DDS(); // constructor
			~cSubLoader_BitmapDevIL_DDS(); // destructor

			//-------------------------------------------------------------------------------------

			void SaveBitmap(cBitmap* apBitmap, const twString& asFile); //UNUSED: save bitmap
			cBitmap* LoadBitmap(const twString& asFile); // load bitmap

			//-------------------------------------------------------------------------------------

		private:

			//-------------------------------------------------------------------------------------

			eBitmapFormat ILtoEnum(ILint aFormat); // enum conversion

			//-------------------------------------------------------------------------------------

		};
	}

#endif
