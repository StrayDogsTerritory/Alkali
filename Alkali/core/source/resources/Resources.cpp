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
// remove these
#include "graphics/Texture.h"
#include "graphics/GraphicsInterface.h"

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
		Log(" Bitmap Loader");
		mpBitmapLoader = alkNew(cBitmapLoader, (this));
		lLoaderList.push_back(mpBitmapLoader);

		Log("Setup external sub-loaders...\n");
		mpResources->SetupBitmapLoader(mpBitmapLoader);
		Log("Done\n");

		Log("Adding resource directories\n");
		//AddDirectory(L"./", true);

		Log("---------------------------------------------\n");
		return true;
	}

	void cResources::OnUpdate(float afStep)
	{
		//@TODO: this is so unbelievably bad that I should be banned from programming. Remove all of this later

		twString sPath = L"test/photomode_03072025_150327.png";
		twString sPathWin = cString::ReplaceW(sPath, L"/", L"\\");

		if (bTest)
		{
			cBitmap* pBitmap = mpBitmapLoader->LoadBitmap(sPathWin);
			bTest = false;

			iTexture* pTexture = mpGraphics->GetLowGraphics()->CreateTexture(cString::To8BitChar(cString::FileNameW(sPath)));
			pTexture->CreateTextureFromBitmap(pBitmap->GetDimensions(), pBitmap);

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