#ifndef ALK_SUBLOADERBITMAP_H
#define ALK_SUBLOADERBITMAP_H

#include "resources/SubLoader.h"

#include "graphics/Bitmap.h"

namespace alk {

	class iSubloader_Bitmap : public iSubLoader
	{
	public:
		iSubloader_Bitmap() {}
		virtual ~iSubloader_Bitmap() {}

		virtual void SaveBitmap(cBitmap* apBitmap, const twString& asFile)=0;
		virtual cBitmap* LoadBitmap(const twString& asFile)=0;
	};
}

#endif
