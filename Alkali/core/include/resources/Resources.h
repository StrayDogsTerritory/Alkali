#ifndef ALK_RESOURCES_H
#define ALK_RESOURCES_H

#include "system/String.h"

#include <map>
#include <list>

namespace alk {

	class cShaderManager;
	class iResourceBase;
	class iResourceManager;
	class cFileSearcher;
	class cGraphics;

	///////////////////////
	//depricated
	typedef std::map<tString, iResourceManager*> tManagerMap;
	typedef tManagerMap::iterator tManagerMapIterator;


	typedef std::list<iResourceManager*> tManagerList;
	typedef tManagerList::iterator tManagerListIt;


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
		tManagerMap mManagermap;
		tManagerList lManagerList;

		cGraphics* mpGraphics;

		cShaderManager* mpShaderManager;
	};

}
#endif
