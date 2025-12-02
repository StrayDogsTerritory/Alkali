#include "engine/Updater.h"
#include "engine/Updateable.h"


namespace alk {

	cUpdater::cUpdater()
	{

	}

	cUpdater::~cUpdater()
	{

	}

	void cUpdater::RunEngineUpdate(eUpdatableMessageType aType, float afStep)
	{
		tEngineModuleListIt it = lEngineModuleList.begin();
		for (; it != lEngineModuleList.end(); it++)
		{
			iUpdateable* pUpdateable = *it;
			pUpdateable->CallMessage(aType, afStep);
		}
	}

	bool cUpdater::AddEngineModule(iUpdateable* apUpdateable)
	{
		lEngineModuleList.push_back(apUpdateable);
		return true;
	}
}