#include "TorMain.h"

int AlkaliMain(const tString& asCommandLine)
{
	
	CreateAlkaliEngine();


	// Initialize the memory manager
	cMemoryManager::MemoryLog();

	return 0;
}