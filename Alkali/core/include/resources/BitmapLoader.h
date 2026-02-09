#ifndef ALK_BITMAPLOADER_H
#define ALK_BITMAPLOADER_H

#include "resources/SubLoader_Bitmap.h"
#include "resources/ResourceLoader.h"

namespace alk {

	class cResources;
	class cGraphics;

	class cBitmapLoader : public iResourceLoader
	{
	public:
		cBitmapLoader(cResources* apResources);
		~cBitmapLoader();

		// loader requirements
		void SetupSubLoader(iSubLoader* apSubLoader);

		cBitmap* LoadBitmap(const twString& asFile);
		void SaveBitmap(cBitmap* apBitmap, const twString& asFile);

	private:

	};
}

#endif
