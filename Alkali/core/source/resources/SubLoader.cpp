#include "resources/SubLoader.h"

namespace alk {

	bool iSubLoader::IsSupported(const twString& asExtension)
	{
		tExtensionIt it = mLstExtensions.begin();
		tString sLowExt = cString::To8BitChar(cString::ToLowerCaseW(asExtension));

		for (; it != mLstExtensions.end(); ++it)
		{
			tString sComp = (*it);

			if (sLowExt == sComp)
				return true;
		}

		return false;
	}

	void iSubLoader::AddExtension(const twString& asExtension)
	{
		mLstExtensions.push_back(cString::To8BitChar(asExtension));
	}
}