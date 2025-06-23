#ifndef ALK_RESOURCEMANAGER_H
#define ALK_RESOURCEMANAGER_H

#include <list>
#include <map>
#include "system/String.h"




namespace alk {

	typedef std::map<tString, iResourceManager* > tmResourceManagers;


	class iResourceManager
	{
	public:
		iResourceManager();
		virtual ~iResourceManager();

	protected:
		

	};

}
#endif
