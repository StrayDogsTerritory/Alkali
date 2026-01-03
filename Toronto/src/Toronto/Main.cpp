#include "BaseGame.h"



cTorGameBase* gpBase = NULL;

int AlkaliMain(const tString& asCommandLine)
{

	gpBase = alkNew(cTorGameBase, ());

	if (gpBase->Init(asCommandLine))
	{
		gpBase->Run();
		gpBase->Exit();
	}

	alkDelete(gpBase);
	// report the memory
	cMemoryManager::MemoryLog();

	return 0;
}