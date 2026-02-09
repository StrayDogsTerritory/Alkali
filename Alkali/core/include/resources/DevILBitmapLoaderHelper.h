#ifndef ALK_DEVILBITMAPLAODERHELPER_H
#define ALK_DEVILBITMAPLOADERHELPER_H

#include "system/String.h"

namespace alk {

	class cBitmap;

	class cDevILBitmapLoaderHelper
	{
	public:
		static bool SaveBitmapDevIL(cBitmap* apBitmap, const twString& asFile);
		static bool LoadBitmapDevIL(const twString& asFile);

	};

}

#endif
