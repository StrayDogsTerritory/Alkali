#include "TorMain.h"

int AlkaliMain(const tString& asCommandLine)
{
	mpGame = NULL;

	mpGame = CreateAlkaliEngine(eEngineInit_All, eEngineAPI_eOpenGl);

	Log("Beginning Game Loop\n");
	mpGame->Run();


	if(mpGame)
		DestroyAlkaliEngine(mpGame);

	// report the memory
	cMemoryManager::MemoryLog();

	return 0;
}