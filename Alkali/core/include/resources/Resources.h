#ifndef ALK_RESOURCES_H
#define ALK_RESOURCES_H

#include "system/String.h"

#include <map>
#include <list>

namespace alk {

	class cShaderManager;
	class iResourceBase;
	class iResourceManager;
	class iResourceLoader;
	class cFileSearcher;
	class cGraphics;


	typedef std::list<iResourceManager*> tManagerList;
	typedef tManagerList::iterator tManagerListIt;

	typedef std::list<iResourceLoader*> tLoaderList;
	typedef tLoaderList::iterator tLoaderIterator;

	class cResources
	{
	public:
		cResources();
		~cResources();

		bool Init(cGraphics* apGraphics);
		
		cFileSearcher* GetFileSearcher() { return mpFileSearcher; }

		cShaderManager* GetShaderManager();

		void AddDirectory(const twString& asDir, bool abAddSubDirs, const tString& asFilter = "*.*");

	private:
		cFileSearcher* mpFileSearcher;
		tManagerList lManagerList;
		tLoaderList lLoaderList;
		cGraphics* mpGraphics;

		cShaderManager* mpShaderManager;
	};

}
#endif
