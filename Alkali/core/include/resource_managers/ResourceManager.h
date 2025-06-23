#ifndef ALK_RESOURCEMANAGER_H
#define ALK_RESOURCEMANAGER_H

#include <list>
#include <map>
#include "system/String.h"




namespace alk {

	typedef std::map<tString, iResourceManager* > tmResourceManagers;
	typedef tmResourceManagers::iterator tmResourceManagersIterator;


	class iResourceManager
	{
	public:
		iResourceManager();
		virtual ~iResourceManager();

	protected:
		

	};

}
#endif
