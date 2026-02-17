#ifndef ALK_RESOURCES_H
#define ALK_RESOURCES_H

#include "system/String.h"
#include "engine/Updateable.h"

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
	class cTextureManager;

	typedef std::list<iResourceManager*> tManagerList;
	typedef tManagerList::iterator tManagerListIt;

	typedef std::list<iResourceLoader*> tLoaderList;
	typedef tLoaderList::iterator tLoaderIterator;

	class cResources : public iUpdateable
	{
	public:
		cResources(iResources* apResources);
		~cResources();

		bool Init(cGraphics* apGraphics);
		
		void OnUpdate(float afStep);

		iResources* GetResources() { return mpResources; }

		cFileSearcher* GetFileSearcher() { return mpFileSearcher; }

		cShaderManager* GetShaderManager() { return mpShaderManager; }
		cTextureManager* GetTextureManager() { return mpTextureManager; }

		cBitmapLoader* GetBitmapLoader() { return mpBitmapLoader; }

		void AddDirectory(const twString& asDir, bool abAddSubDirs, const tString& asFilter = "*.*");

	private:
		cFileSearcher* mpFileSearcher;
		cGraphics* mpGraphics;
		iResources* mpResources;

		tManagerList lManagerList;
		tLoaderList lLoaderList;
		
		static bool bTest;

		cShaderManager* mpShaderManager;
		cTextureManager* mpTextureManager;

		cBitmapLoader* mpBitmapLoader;
	};

}
#endif
