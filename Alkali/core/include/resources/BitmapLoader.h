#ifndef ALK_BITMAPLOADER_H
#define ALK_BITMAPLOADER_H

#include "resources/SubLoader_Bitmap.h"
#include "resources/ResourceLoader.h"

/*
* Created by Simon Stroomer
* bitmap loader, which contains specific loaders for each file type
*/

namespace alk {

	class cResources;
	class cGraphics;

	class cBitmapLoader : public iResourceLoader
	{
	public:

		//-------------------------------------------------------------------------------------

		cBitmapLoader(cResources* apResources); // constructor
		~cBitmapLoader(); //destructor

		//-------------------------------------------------------------------------------------

		// loader requirements
		void SetupSubLoader(iSubLoader* apSubLoader); // setup any specifics for the sub loader

		//-------------------------------------------------------------------------------------

		cBitmap* LoadBitmap(const twString& asFile); //loads a bitmap from disk
		void SaveBitmap(cBitmap* apBitmap, const twString& asFile); // UNUSED: saves bitmap to disk

		//-------------------------------------------------------------------------------------

	private:

	};
}

#endif
