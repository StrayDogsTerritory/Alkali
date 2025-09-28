#include "system/LogicTimer.h"

#include "system/Platform.h"

namespace alk {

	cLogicTimer::cLogicTimer(int alUpdatesPerSec)
	{
		mlUpdateCount = 0;
		mlMaxUpdates = alUpdatesPerSec / alUpdatesPerSec;

		SetUpdatesPerSecond(alUpdatesPerSec);

		Reset();
	}

	cLogicTimer::~cLogicTimer()
	{

	}

	void cLogicTimer::Reset()
	{
		mfTime =  (double)cPlatform::GetAppTime();
	}

	bool cLogicTimer::CanUpdate()
	{
		if (mlUpdateCount > mlMaxUpdates) {
			return false;
		}

		if (mfTime < (double)cPlatform::GetAppTime())
		{
			Update();
			return true;
		}

		return false;
	}

	void cLogicTimer::Update()
	{
		mfTime += mfTimeAdd;
	}

	void cLogicTimer::EndLoop()
	{
		if (mlUpdateCount > mlMaxUpdates)
		{
			Reset();
		}
		mlUpdateCount = 0;
	}

	int cLogicTimer::GetUpdatesPerSecond()
	{
		return ((int)(1000.0f / mfTimeAdd));
	}

	void cLogicTimer::SetUpdatesPerSecond(int alUpdatePerSeconds)
	{
		mfTimeAdd = (double)(1000.0f / (float)(alUpdatePerSeconds));
		Reset();
	}

	float cLogicTimer::GetStepSize()
	{
		return ((float)mfTimeAdd / 1000.0f);
	}
}