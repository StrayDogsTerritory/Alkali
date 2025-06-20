#ifndef ALK_RESOURCEMANAGER_H
#define ALK_RESOURCEMANAGER_H

#include <list>
#include <map>

namespace alk {

	class cResourceManager
	{
	public:
		cResourceManager();
		~cResourceManager();
	
	private:
	typedef	std::list<void*> tmlstResourceManagers; // list of all resource managers
	};

}
#endif
