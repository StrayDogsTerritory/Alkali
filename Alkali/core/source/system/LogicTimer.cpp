#include "system/LogicTimer.h"

#include "system/Platform.h"

namespace alk {
	cLogicTimer::cLogicTimer(unsigned int alUpdatesPerSecond)
	{
		mlMaxUpdates = alUpdatesPerSecond/10;
		mlUpdateCount = 0;

		// reset the timer
		SetUpdatesPerSecond(alUpdatesPerSecond);
	}

	bool cLogicTimer::WantUpdate()
	{
		++mlUpdateCount;
		if (mlUpdateCount > mlMaxUpdates)
		{
			return false;
		}

		if (mfCurrentTime < (double)cPlatform::GetAppTime())
		{
			Update();
			return true;
		}

		return false;
	}

	void cLogicTimer::Reset()
	{
		mfCurrentTime = (double)cPlatform::GetAppTime();
	}

	unsigned int cLogicTimer::GetupdatesPerSecond()
	{
		return (unsigned int)(1000.0f / mfUpdatesPerSec);
	}

	void cLogicTimer::Update()
	{
		mfCurrentTime += mfUpdatesPerSec;
	}

	void cLogicTimer::EndLoop()
	{
		if (mlUpdateCount > mlMaxUpdates)
		{
			Reset();
		}

		mlUpdateCount = 0;
	}

	void cLogicTimer::SetUpdatesPerSecond(unsigned int alUpdatesPerSecond)
	{
		mfUpdatesPerSec = 1000.0f / ((double)alUpdatesPerSecond);
		Reset();
	}
}