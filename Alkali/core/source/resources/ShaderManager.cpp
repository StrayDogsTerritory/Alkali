#include "resources/ResourceBase.h"
#include "resources/ShaderManager.h"
#include "resources/Resources.h"

#include "graphics/Shader.h"
#include "graphics/Graphics.h"
#include "graphics/GraphicsInterface.h"

#include "engine/LogWriter.h"

namespace alk {

	cShaderManager::cShaderManager(cGraphics* apGraphics, cResources* apResources)
		: iResourceManager(apResources->GetFileSearcher(), apGraphics->GetLowGraphics())
	{
		mpGraphics = apGraphics;
		mpResources = apResources;
	}

	cShaderManager::~cShaderManager()
	{
		DestroyAll();
		Log("Destroyed ShaderManager");
	}


	iShader* cShaderManager::CreateShader(const tString& asName, eShaderType aType)
	{
		twString sPath;
		iShader* pShader = static_cast<iShader*> (FindResource(asName, sPath));

		if (pShader == NULL && sPath != L"")
		{
			pShader = mpGraphicsI->CreateShader(asName, aType);

			if (!pShader->CreateFromFile(sPath))
			{
				Error("Could not Create Shader '%s' at '%s'!\n", asName.c_str(), cString::To8BitChar(sPath).c_str());
				alkDelete(pShader);
				return NULL;
			}

			AddResource(pShader);
			Log("added as resource\n");
		}

		if (pShader) { pShader->AddUser(); Log("added manager as a user\n"); }
		else Error("Couldn't load Shader '%s'\n", asName.c_str());

		Log("returned\n");
		return pShader;
	}

	void cShaderManager::Delete(iResourceBase* apResource)
	{
		apResource->RemoveUser();

		if (apResource->HasUsers() == false)
		{
			RemoveResource(apResource);
			alkDelete(apResource);
		}
	}
}