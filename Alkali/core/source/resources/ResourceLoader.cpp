#include "resources/SubLoader.h"
#include "resources/ResourceLoader.h"
#include "resources/Resources.h"

#include "engine/LogWriter.h"

#include "system/SystemTypes.h"

namespace alk {

	iResourceLoader::iResourceLoader(cResources* apResources)
	{
		mpResources = apResources; // points to the main resource module
	}

	//-------------------------------------------------------------------------------------

	iResourceLoader::~iResourceLoader()
	{
		DeleteAll(mvSubLoaders); // deletes every sub loader pointer in the array
	}

	//-------------------------------------------------------------------------------------

	void iResourceLoader::AddSubLoader(iSubLoader* apSubLoader)
	{
		mvSubLoaders.push_back(apSubLoader); // add the subloader to the array

		// loader specific setup
		SetupSubLoader(apSubLoader);

		// add supported extensions to loader
		tStringList::iterator it = apSubLoader->mLstExtensions.begin(); // create an iterator
		for (; it != apSubLoader->mLstExtensions.end(); ++it)
		{
			tString sExt = *it; // dereference the value in the iterator into a variable
			mLstSupportedExtensions.push_back(sExt); //add the extensions to this loader
		}
	}

	//-------------------------------------------------------------------------------------

	iSubLoader* iResourceLoader::GetSubLoaderForFile(const twString& asFile)
	{
		tString sExt = cString::To8BitChar(cString::FileExtensionW(asFile)); // get the ASCII file extension from the std::wstring file

		for (int i = 0; i < mvSubLoaders.size(); ++i) // for every sub loader
		{
			iSubLoader* pSubLoader = mvSubLoaders[i]; // save it in scope
			if (pSubLoader) { // if the value at i is non-NULL
				if (pSubLoader->IsSupported(sExt)) // if the extension is supported by one of the sub loaders
				{
					return pSubLoader; // return it
				}
			}
		}
		// if we can't find anything good
		Error("Couldn't find suitable sub-loader for file extension '%s'\n", sExt.c_str()); //let the user know we couldn't find a good sub loader
		return NULL; //return NULL
	}

	//-------------------------------------------------------------------------------------
}