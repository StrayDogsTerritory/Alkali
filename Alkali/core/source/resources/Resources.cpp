#include "engine/LogWriter.h"

#include "resources/Resources.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderManager.h"
#include "resources/FileSearcher.h"

#include "system/SystemTypes.h"

#include "graphics/Graphics.h"

namespace alk {

	cResources::cResources()
	{
		mpFileSearcher = alkNew(cFileSearcher, ());
	}

	cResources::~cResources()
	{
		Log("Destroying Managers\n");
		alkDelete(mpShaderManager);
		Log("Destroyed All Managers\n");

		alkDelete(mpFileSearcher);

	}

	bool cResources::Init(cGraphics* apGraphics)
	{
		mpGraphics = apGraphics;
		mpShaderManager = alkNew(cShaderManager, (mpGraphics, this));
		lManagerList.push_back(mpShaderManager);

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