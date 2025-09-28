#ifndef ALK_RESOURCEMANAGER_H
#define ALK_RESOURCEMANAGER_H

#include <list>
#include <map>
#include "system/String.h"




namespace alk {

	class iResourceBase;
	class cFileSearcher;
	class cResources;
	class iGraphics;

	typedef std::multimap<unsigned int, iResourceBase* > tmResources;
	typedef tmResources::iterator tmResourcesIterator;


	class iResourceManager
	{
	public:
		iResourceManager( cFileSearcher* apFileSearcher, iGraphics* apGraphics);
		virtual ~iResourceManager() {};

		void AddResource(iResourceBase* apResource);
		void RemoveResource(iResourceBase* apResource);

		void DestroyAll();

		void UnloadUnused();
		void DeleteUnused();

		virtual void Unload(iResourceBase* apResource)=0;
		virtual void Delete(iResourceBase* apResource)=0;
		virtual void Reload(iResourceBase* apResource)=0;
		virtual void Preload(iResourceBase* apResource)=0;


		iResourceBase* GetResource(const twString& asPath);
	protected:
		iResourceBase* FindResource(const tString& asName, twString &asFilePath);

		cFileSearcher* mpFileSearcher;
		iGraphics* mpGraphicsI;

		tmResources mResources;
	};

}
#endif
