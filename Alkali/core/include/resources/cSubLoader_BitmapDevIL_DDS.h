#ifndef ALK_SUBLOADERBITMAPDEVILDDS_H
#define ALK_SUBLOADERBITMAPDEVILDDS_H
#include "resources/SubLoader_Bitmap.h"

#include <IL/il.h>

	namespace alk {

		class cSubLoader_BitmapDevIL_DDS : public iSubloader_Bitmap
		{
		public:
			cSubLoader_BitmapDevIL_DDS();
			~cSubLoader_BitmapDevIL_DDS();

			void SaveBitmap(cBitmap* apBitmap, const twString& asFile);
			cBitmap* LoadBitmap(const twString& asFile);

		private:
			eBitmapFormat ILtoEnum(ILint aFormat);
		};
	}

#endif
