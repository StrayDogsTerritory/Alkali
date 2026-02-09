#include "resources/SubLoader.h"
#include "resources/ResourceLoader.h"
#include "resources/Resources.h"

#include "engine/LogWriter.h"

#include "system/SystemTypes.h"

namespace alk {

	iResourceLoader::iResourceLoader(cResources* apResources)
	{
		mpResources = apResources;
	}



	iResourceLoader::~iResourceLoader()
	{
		DeleteAll(mvSubLoaders);
	}



	void iResourceLoader::AddSubLoader(iSubLoader* apSubLoader)
	{
		mvSubLoaders.push_back(apSubLoader);

		// loader specific setup
		SetupSubLoader(apSubLoader);

		// add supported extensions to loader
		tStringList::iterator it = apSubLoader->mLstExtensions.begin();
		for (; it != apSubLoader->mLstExtensions.end(); ++it)
		{
			tString sExt = *it;
			mLstSupportedExtensions.push_back(sExt);
		}
	}



	iSubLoader* iResourceLoader::GetSubLoaderForFile(const twString& asFile)
	{
		tString sExt = cString::To8BitChar(cString::FileExtensionW(asFile));

		for (int i = 0; i < mvSubLoaders.size(); ++i)
		{
			iSubLoader* pSubLoader = mvSubLoaders[i];
			if (pSubLoader) {
				if (pSubLoader->IsSupported(sExt))
				{
					return pSubLoader;
				}
			}
		}
		Error("Couldn't find suitable sub loader for file extension '%s'\n", sExt.c_str());
		return NULL;
	}
}