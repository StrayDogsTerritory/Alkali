#include "system/MemoryManager.h"



namespace alk {
	alk::cAllocatedPointer::cAllocatedPointer(void* apData, const std::string& asFile, int alLine, size_t alMemory)
	{
		mpData = apData;
		msFile = asFile;
		mlLine = alLine;
		mlMemory = alMemory;
	}
	


}