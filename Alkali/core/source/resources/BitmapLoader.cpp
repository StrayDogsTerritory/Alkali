#include "resources/Resources.h"
#include "resources/BitmapLoader.h"
#include "resources/SubLoader_Bitmap.h"

namespace alk {

	cBitmapLoader::cBitmapLoader(cResources* apResources) : iResourceLoader(apResources)
	{

	}

	cBitmapLoader::~cBitmapLoader()
	{

	}

	void cBitmapLoader::SetupSubLoader(iSubLoader* apSubLoader)
	{

	}

	cBitmap* cBitmapLoader::LoadBitmap(const twString& asFile)
	{
		iSubloader_Bitmap* pLoader = static_cast<iSubloader_Bitmap*> (GetSubLoaderForFile(asFile));

		cBitmap* pBitmap = pLoader->LoadBitmap(asFile);

		return pBitmap;
	}

}