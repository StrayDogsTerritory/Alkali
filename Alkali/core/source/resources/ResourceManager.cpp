#include "resources/ResourceManager.h"
#include "resources/ResourceBase.h"
#include "resources/FileSearcher.h"
#include "resources/Resources.h"

#include "engine/LogWriter.h"
#include "graphics/GraphicsInterface.h"

namespace alk {

	iResourceManager::iResourceManager(cFileSearcher* apFileSearcher, iGraphics* apGraphics)
	{
		mpFileSearcher = apFileSearcher;
		mpiGraphics = apGraphics;
	}

	void iResourceManager::AddResource(iResourceBase* apResource)
	{
		tString sName = cString::ToLowerCase(apResource->GetName());
		unsigned int lHash = cString::Hash(sName);

		mResources.insert(tmResources::value_type(lHash, apResource));
	}



	iResourceBase* iResourceManager::GetResource(const twString& asPath)
	{
		unsigned int lHash = cString::Hash(cString::To8BitChar(cString::ToLowerCaseW(asPath)));

		tmResourcesIterator it = mResources.find(lHash);
		if (it == mResources.end()) {
			//Error("Couldn't find Resource '%u'\n", lHash);
			return NULL;
		}

		size_t lDupes = mResources.count(lHash);
		for (int i = 0; i < lDupes; ++i, it++)
		{
			iResourceBase* pResource = it->second;
			if (pResource->GetPath() == asPath)
				return pResource;

		}

		return NULL;
	}


	iResourceBase* iResourceManager::FindResource(const tString& asName, twString &asFilePath)
	{ 
		asFilePath = mpFileSearcher->GetPath(asName);
		iResourceBase* pResource = GetResource(asFilePath);
		if (pResource != NULL)
		{
			asFilePath = L"";
		}
		return pResource;
	}



	void iResourceManager::RemoveResource(iResourceBase* apResource)
	{
		unsigned int lHash = cString::Hash(cString::ToLowerCase(apResource->GetName()));

		tmResourcesIterator it = mResources.find(lHash);
			if (it == mResources.end())
			{
				Error("'%d' Resource '%s' cannot be found!\n", apResource, apResource->GetName().c_str());
				return;
			}
		size_t lDupes = mResources.count(lHash);
		for (int i = 0; i < lDupes; ++i, ++it)
		{
			iResourceBase* pResource = it->second;

			if (pResource == apResource)
			{
				mResources.erase(it);
				return;
			}
		}
	}

	void iResourceManager::DestroyAll()
	{
		tmResourcesIterator it = mResources.begin();
		//Debug("Resource: %s UserCount: %u, Hash: %u\n", it->second->GetName().c_str(), it->second->NumUsers(), it->first);
		if (it == mResources.end()) return;

		while ((it != mResources.end()))
		{
			iResourceBase* pResource = it->second;

			while (pResource->HasUsers())
			{
				pResource->RemoveUser();
			}

			Delete(pResource);

			it = mResources.begin();
		}
	}

	void iResourceManager::DeleteUnused()
	{

	}

	void iResourceManager::UnloadUnused()
	{

	}
}