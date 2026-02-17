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
	}


	iShader* cShaderManager::CreateShader(const tString& asName, eShaderType aType)
	{
		twString sPath = cPlatform::GetFullFilePath(cString::ToWideChar(asName));
		iShader* pShader = static_cast<iShader*> (FindResource(asName, sPath));

		if (pShader == NULL && sPath != L"")
		{
			pShader = mpiGraphics->CreateShader(asName, aType);

			if (!pShader->CreateFromFile(sPath))
			{
				Error("Could not create shader '%s' at '%s'!\n", asName.c_str(), cString::To8BitChar(sPath).c_str());
				alkDelete(pShader);
				return NULL;
			}

			AddResource(pShader);
		}

		if (pShader) 
		{ 
			pShader->AddUser();
		}
		else Error("Couldn't load Shader '%s'!\n", asName.c_str());

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