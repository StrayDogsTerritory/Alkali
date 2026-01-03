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
		for (tEngineModuleListIt it = lEngineModuleList.begin(); it != lEngineModuleList.end(); it++)
		{
			iUpdateable* pUpdateable = *it;
			pUpdateable->CallMessage(aType, afStep);
		}

		// @TODO: make a seperate func to update both game and engine modules together
		
		for (tAppModuleIt Mapit = mAppModuleMap.begin(); Mapit != mAppModuleMap.end(); ++Mapit)
		{
			iUpdateable* pUpdateable = Mapit->second;
			pUpdateable->CallMessage(aType, afStep);
		}
	}

	bool cUpdater::AddEngineModule(iUpdateable* apUpdateable)
	{
		lEngineModuleList.push_back(apUpdateable);
		return true;
	}

	void cUpdater::AddAppContainer(const tString& asName, iUpdateable* apUpdateable)
	{
		tApplicationModuleMap::value_type val = tApplicationModuleMap::value_type(asName, apUpdateable);
		mAppModuleMap.insert(val);
	}
}