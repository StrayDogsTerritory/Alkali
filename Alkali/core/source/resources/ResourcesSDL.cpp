#include "resources/ResourcesSDL.h"
#include "resources/SubLoader_BitmapDevIL.h"
#include "resources/ResourceLoader.h"
#include "engine/LogWriter.h"

#include <IL/il.h>

namespace alk {

	cResourcesSDL::cResourcesSDL() : iResources()
	{
	
	}

	cResourcesSDL::~cResourcesSDL()
	{

	}

	bool cResourcesSDL::Init()
	{
		// init DevIL
		Log("Initilizing DevIL\n");
		ilInit();
		Log("---DevIL Specifics---\n");
		Log("Version: %d\n",ilGetInteger(IL_VERSION));
		Log("Vendor: %d\n",ilGetInteger(IL_VENDOR));
		Log("\n");

		return true;
	}

	void cResourcesSDL::SetupBitmapLoader(iResourceLoader* apResourceLoader)
	{
		apResourceLoader->AddSubLoader(alkNew(cSubLoader_BitmapDevIL, ()));
	}

}