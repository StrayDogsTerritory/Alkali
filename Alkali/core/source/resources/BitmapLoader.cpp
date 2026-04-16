#include "resources/Resources.h"
#include "resources/BitmapLoader.h"
#include "resources/SubLoader_Bitmap.h"

namespace alk {

	cBitmapLoader::cBitmapLoader(cResources* apResources) : iResourceLoader(apResources)
	{
		//does nothing
	}

	//-------------------------------------------------------------------------------------

	cBitmapLoader::~cBitmapLoader()
	{
		// does nothing
	}

	//-------------------------------------------------------------------------------------

	void cBitmapLoader::SetupSubLoader(iSubLoader* apSubLoader)
	{
		// does nothing
	}

	//-------------------------------------------------------------------------------------

	cBitmap* cBitmapLoader::LoadBitmap(const twString& asFile)
	{
		iSubloader_Bitmap* pLoader = static_cast<iSubloader_Bitmap*> (GetSubLoaderForFile(asFile)); // get the proper sub loader for the file, downcast it

		cBitmap* pBitmap = pLoader->LoadBitmap(asFile); //load the bitmap from the specific sub loader

		return pBitmap;
	}

	//-------------------------------------------------------------------------------------
}