#ifndef ALK_RESOURCES_H
#define ALK_RESOURCES_H

#include "system/String.h"

#include <map>
#include <list>

namespace alk {

	class cBitmapLoader;
	class cShaderManager;
	class iResourceBase;
	class iResourceManager;
	class iResourceLoader;
	class cFileSearcher;
	class cGraphics;
	class iResources;

	typedef std::list<iResourceManager*> tManagerList;
	typedef tManagerList::iterator tManagerListIt;

	typedef std::list<iResourceLoader*> tLoaderList;
	typedef tLoaderList::iterator tLoaderIterator;

	class cResources
	{
	public:
		cResources(iResources* apResources);
		~cResources();

		bool Init(cGraphics* apGraphics);
		
		iResources* GetResources() { return mpResources; }

		cFileSearcher* GetFileSearcher() { return mpFileSearcher; }

		cShaderManager* GetShaderManager();

		cBitmapLoader* GetBitmapLoader() { return mpBitmapLoader; }

		void AddDirectory(const twString& asDir, bool abAddSubDirs, const tString& asFilter = "*.*");

	private:
		cFileSearcher* mpFileSearcher;
		cGraphics* mpGraphics;
		iResources* mpResources;

		tManagerList lManagerList;
		tLoaderList lLoaderList;
		
		

		cShaderManager* mpShaderManager;

		cBitmapLoader* mpBitmapLoader;
	};

}
#endif
