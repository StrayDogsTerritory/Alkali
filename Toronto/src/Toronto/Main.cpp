#include "TorMain.h"

int AlkaliMain(const tString& asCommandLine)
{
	mpGame = CreateAlkaliEngine();

	if(mpGame)
		DestroyAlkaliEngine(mpGame);

	// Initialize the memory manager
	cMemoryManager::MemoryLog();

	return 0;
}