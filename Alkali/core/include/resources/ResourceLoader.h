#ifndef  ALK_RESOURCELOADER_H
#define ALK_RESOURCELOADER_H

#include "system/String.h"

#include <vector>

namespace alk
{
	class cResources;
	class iSubLoader;

	class iResourceLoader
	{
	public:
		iResourceLoader(cResources* apResources);
		virtual ~iResourceLoader();

		void AddSubLoader(iSubLoader* apSubLoader);

		void AddSupportedExtension(const twString& asExtension);
		iSubLoader* GetLoaderForFile(const twString& asFile);

	private:
		std::vector<iSubLoader*> mvSubLoaders;
		std::vector<tString> mvSupportedExtensions;
	};

}

#endif
