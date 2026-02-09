#ifndef  ALK_RESOURCELOADER_H
#define ALK_RESOURCELOADER_H

#include "system/String.h"

#include <list>
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

		virtual void SetupSubLoader(iSubLoader* apSubLoader)=0;

		//void AddSupportedExtension(const twString& asExtension);
		iSubLoader* GetSubLoaderForFile(const twString& asFile);

	protected:
		cResources* mpResources;

		std::vector<iSubLoader*> mvSubLoaders;
		std::list<tString> mLstSupportedExtensions;
	};

}

#endif
