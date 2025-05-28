#include "TorMain.h"

int AlkaliMain(const tString& asCommandLine)
{
	mpGame = NULL;

	mpGame = CreateAlkaliEngine();

	mpGame->Run();

	if(mpGame)
		DestroyAlkaliEngine(mpGame);

	// Initialize the memory manager
	cMemoryManager::MemoryLog();

	return 0;
}