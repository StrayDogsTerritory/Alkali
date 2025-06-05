#ifndef ALK_MEMORYMANAGER_H
#define ALK_MEMORYMANAGER_H

#include <map>
#include <string>

namespace alk {

	class cAllocatedPointer
	{
	public:
		cAllocatedPointer(void* apData, const std::string& asFile, int alLine, size_t alMemorySize);

		void* mpData;
		std::string msFile;
		int mlLine;
		size_t mlMemorySize;

	};


	typedef std::map <void*, cAllocatedPointer> tAllocatedPointerMap;
	typedef std::map <void*, cAllocatedPointer>::iterator tAllocatedPointermapIterator;

	class cMemoryManager
	{
	public:
		static void* AddPointer(const cAllocatedPointer& asAllocatedPointer);
		static bool DeletePointer(void* apData, const char* apFileString, int alLine);
		static void* UpdatePointer(void* apOldData, const cAllocatedPointer& aNewAllocatedPointer);

		static void MemoryLog();

		static tAllocatedPointerMap m_mapPointers;
		static size_t mlTotalMemoryUsage;

		template<class T>
		static T* DeleteAndReturn(T* apData)
		{
			delete apData;
			return apData;
		}

		template<class T>
		static T* DeleteArrayAndReturn(T* apData)
		{
			delete[] apData;
			return apData;
		}

		template<class T>
		static T* FreeAndReturn(T* apData)
		{
			free(apData);
			return apData;
		}

	};

	

#define alkNew(constructor, params) \
	( constructor* ) cMemoryManager::AddPointer(alk::cAllocatedPointer( new constructor params, __FILE__, __LINE__, sizeof(constructor)))

#define alkNewArray(constructor, amount) \
	( classType* ) cMemoryManager::AddPointer(alk::cAllocatedPointer( new constructor[amount], __FILE__, __LINE__, amount * sizeof(constructor) )))

#define alkMalloc(amount) \
	 cMemoryManager::AddPointer(alk::cAllocatedPointer( malloc(size), __FILE__, __LINE__, amount))

#define alkRealloc(oldPointer, amount) \
	 cMemoryManager::UpdatePointer(oldPointer, alk::cAllocatedPointer( realloc(oldPointer, size), __FILE__, __LINE__, amount))

#define alkDelete(data){ \
			alk::cMemoryManager::DeletePointer(alk::cMemoryManager::DeleteAndReturn(data),__FILE__,__LINE__); \
			}
#define alkDeleteArray(data){ \
	alk::cMemoryManager::DeletePointer(alk::cMemoryManager::DeleteArrayAndReturn(data), __FILE__, __LINE__); \
	}
#define alkFree(data){ \
	alk::cMemoryManager::DeletePointer(alk::cMemoryManager::FreeAndReturn(data), __FILE__, __LINE__); \
	}

}
#endif
