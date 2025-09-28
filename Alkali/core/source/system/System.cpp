#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/MemoryManager.h"

namespace alk {

	cSystem::cSystem()

	cLogicTimer* cSystem::CreateLogicTimer(unsigned int alUpdatesPerSec)
	{
		return alkNew(cLogicTimer, (alUpdatesPerSec));
	}

}