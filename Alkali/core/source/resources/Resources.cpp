#include "engine/LogWriter.h"

#include "resources/Resources.h"
#include "resources/ResourceInterface.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderManager.h"
#include "resources/FileSearcher.h"
#include "resources/ResourceLoader.h"
#include "resources/BitmapLoader.h"

#include "system/SystemTypes.h"

#include "graphics/Graphics.h"

namespace alk {

	cResources::cResources(iResources* apResources)
	{
		mpResources = apResources;
		mpGraphics = NULL;

		mpShaderManager = NULL;

		mpBitmapLoader = NULL;

		mpFileSearcher = NULL;//alkNew(cFileSearcher, ());
	}

	cResources::~cResources()
	{
		Log("Quitting Resource module\n");
		Log("---------------------------------------------\n");
		Log("Exiting resource managers\n");
		alkDelete(mpShaderManager);
		Log(" Shader manager\n");

		Log("Exiting filesearcher\n");
		alkDelete(mpFileSearcher);

		Log("---------------------------------------------\n\n");
	}

	bool cResources::Init(cGraphics* apGraphics)
	{
		Log("---------------------------------------------\n");
		mpGraphics = apGraphics;

		mpResources->Init();

		Log("Creating file searcher\n");
		mpFileSearcher = alkNew(cFileSearcher, ());

		Log("Creating resource managers\n");
		Log(" Shader Manager\n");
		mpShaderManager = alkNew(cShaderManager, (mpGraphics, this));
		lManagerList.push_back(mpShaderManager);

		Log("Creating resource loaders\n");
		mpBitmapLoader = alkNew(cBitmapLoader, (this));
		lLoaderList.push_back(mpBitmapLoader);

		Log("Setup external sub-loaders\n");
		

		Log("Adding resource directories\n");
		//AddDirectory(L"./", true);

		Log("---------------------------------------------\n");
		return true;
	}

	// temp
	cShaderManager* cResources::GetShaderManager()
	{
		return mpShaderManager;
	}

	void cResources::AddDirectory(const twString& asDir, bool abAddSubDirs, const tString& asFilter)
	{
		mpFileSearcher->AddDir(asDir, asFilter, abAddSubDirs);
	}


}