#include "resources/SubLoader.h"

namespace alk {

	//-------------------------------------------------------------------------------------

	bool iSubLoader::IsSupported(const tString& asExtension)
	{
		tExtensionIt it = mLstExtensions.begin(); // create a std::list iterator
		tString sLowExt = cString::ToLowerCase(asExtension); //put the extension to lowercase, so we can make searching for it easier

		for (; it != mLstExtensions.end(); ++it) // loop through the list
		{
			tString sComp = (*it); // save the value of the iterator to a variable

			if (sLowExt == sComp) // if the extension is the same as the comparitor
				return true;
		}

		return false; // by default the extension isn't supported
	}

	//-------------------------------------------------------------------------------------

	void iSubLoader::AddExtension(const tString& asExtension)
	{
		mLstExtensions.push_back(asExtension); // push the extension into the list
	}

	//-------------------------------------------------------------------------------------
}