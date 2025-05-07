#ifndef ALK_MEMORYMANAGER_H
#define ALK_MEMORYMANAGER_H

#include <map>
#include <string>

namespace alk {
	
	class cAllocatedPointer
	{
	public:
		cAllocatedPointer(void* asData, std::string asFile, int alLine, size_t alMemory);

		void* mpData;
		std::string msFile;
		int mlLine;
		size_t mlMemory;

	};

	typedef std::map<void*, cAllocatedPointer> tAllocatedPointerMap;


	class cMemoryManager
	{
	public:
		static void* AllocatePointer(const cAllocatedPointer& aAllocatedPointer);
		static void* UpdatePointer(void* apOldData, const cAllocatedPointer& aAllocatedPointer);
		static bool RemovePointer(const void* apOldData, const char* apFileString, int alLine);

		void LogResults();
	};


#define alkNew (classType, constructor) \
		(classType* ) alk::cMemoryManager::AllocatePointer(cAllocatedPointer(new classType Constructor, __FILE__, __LINE__, sizeof (classType)))

}
#endif 
