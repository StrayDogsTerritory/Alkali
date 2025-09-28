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
		Log("Beginning cResources Destructor\n");
		alkDelete(mpShaderManager);
		Log("Destroyed All Managers\n");

		alkDelete(mpFileSearcher);

		Log("Ending cResources Destructor");
	}

	bool cResources::Init(cGraphics* apGraphics)
	{
		mpGraphics = apGraphics;
		mpShaderManager = alkNew(cShaderManager, (mpGraphics, this));
		lManagerList.push_back(mpShaderManager);

		mpGraphics->CreateShaderProgram("Test Program", "test_frag.glsl", "test_vert.glsl");

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