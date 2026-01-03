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

	//@TODO: temp, when Tor matures add more support for game containers
	typedef std::map<tString, iUpdateable*> tApplicationModuleMap;
	typedef tApplicationModuleMap::iterator tAppModuleIt;


	class cUpdater
	{
	public:
		cUpdater();
		~cUpdater();
		void RunEngineUpdate(eUpdatableMessageType aType, float afStep);

		bool AddEngineModule(iUpdateable* apUpdateable);

		void AddAppContainer(const tString& asName, iUpdateable* apUpdateable);

	private:
		tEngineModuleList lEngineModuleList;
		tApplicationModuleMap mAppModuleMap;
		// figure this out later
		void PushUpdateToThread();
	};

}

#endif
