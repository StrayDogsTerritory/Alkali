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

	bool cResources::bTest = true;

	cResources::cResources(iResources* apResources) : iUpdateable("Resources")
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

		Log("Exiting resource loaders\n");
		alkDelete(mpBitmapLoader);
		Log(" Bitmap Loader\n");

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
		mpResources->SetupBitmapLoader(mpBitmapLoader);

		Log("Adding resource directories\n");
		//AddDirectory(L"./", true);

		Log("---------------------------------------------\n");
		return true;
	}

	void cResources::OnUpdate(float afStep)
	{
		twString sPath = L"X:/Alkali/Toronto/redist/test/progress_screen.png";
		twString sPathWin = cString::ReplaceW(sPath, L"/", L"\\");

		if (bTest)
		{
			cBitmap* pBitmap = mpBitmapLoader->LoadBitmap(sPathWin);
			bTest = false;

			alkDelete(pBitmap);
		}
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