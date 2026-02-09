#include "resources/SubLoader.h"

namespace alk {

	bool iSubLoader::IsSupported(const tString& asExtension)
	{
		tExtensionIt it = mLstExtensions.begin();
		tString sLowExt = cString::ToLowerCase(asExtension);

		for (; it != mLstExtensions.end(); ++it)
		{
			tString sComp = (*it);

			if (sLowExt == sComp)
				return true;
		}

		return false;
	}

	void iSubLoader::AddExtension(const tString& asExtension)
	{
		mLstExtensions.push_back(asExtension);
	}
}