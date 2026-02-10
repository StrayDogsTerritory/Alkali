#ifndef ALK_SUBLOADERBITMAPDEVIL_H
#define ALK_SUBLOADERBITMAPDEVIL_H

#include "resources/SubLoader_Bitmap.h"

#include <IL/il.h>

namespace alk {

	class cSubLoader_BitmapDevIL : public iSubloader_Bitmap
	{
		
	public:
	//	friend class cDevILBitmapLoaderHandler;

		cSubLoader_BitmapDevIL();
		~cSubLoader_BitmapDevIL();

		 void SaveBitmap(cBitmap* apBitmap,const twString& asFile);
		 cBitmap* LoadBitmap(const twString& asFile);

	private:
		 eBitmapFormat ILtoEnum(ILint aFormat);
	};
}

#endif
