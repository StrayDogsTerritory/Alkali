#ifndef ALK_MEMORY_MANAGER
#define ALK_MEMORY_MANAGER

#include <map>
#include <string>

namespace alk {

	class cAllocatedPointer
	{
	public:
		cAllocatedPointer(const void*& apData, const std::string& asFile, int alLine, size_t asMemorySize);

	};

	class cMemoryManager
	{
	public:
		static void AddPointer(cAllocatedPointer& aAllocatedPointer);
		static void UpdatePointer(const void* apOldData)

	};
}
#endif
