#ifndef ALK_UPDATER_H
#define ALK_UPDATER_H

#include <list>
#include <map>

#include "engine/Updateable.h"

#include "system/String.h"


namespace alk {

	class iUpdateable;
	class iThread;

	typedef std::list<iUpdateable*> tEngineModuleList;
	typedef tEngineModuleList::iterator tEngineModuleListIt;

	class cUpdater
	{
	public:
		cUpdater();
		~cUpdater();
		void RunEngineUpdate(eUpdatableMessageType aType, float afStep);

		bool AddEngineModule(iUpdateable* apUpdateable);

	private:
		tEngineModuleList lEngineModuleList;
		// figure this out later
		void PushUpdateToThread();
	};

}

#endif
