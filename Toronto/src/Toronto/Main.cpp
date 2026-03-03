#include "BaseGame.h"



cOzyGameBase* gpBase = NULL;

int AlkaliMain(const tString& asCommandLine)
{

	gpBase = alkNew(cOzyGameBase, ());

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