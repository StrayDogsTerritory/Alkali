#include "system/MemoryManager.h"
#include "engine/LogWriter.h"


namespace alk {

	tAllocatedPointerMap cMemoryManager::m_mapPointers;
	size_t cMemoryManager::mlTotalMemoryUsage = 0;

	cAllocatedPointer::cAllocatedPointer(void* apData, const std::string& asFile, int alLine, size_t alMemorySize)
	{
		mpData = apData;
		msFile = asFile;
		mlLine = alLine;
		mlMemorySize = alMemorySize;
	}

	void * cMemoryManager::AddPointer(const cAllocatedPointer& asAllocatedPointer)
	{
		m_mapPointers.insert(tAllocatedPointerMap::value_type(asAllocatedPointer.mpData,asAllocatedPointer));
		mlTotalMemoryUsage += asAllocatedPointer.mlMemorySize;

		//Log("Creating a Pointer 0x%x at: %s, line: %d\n", asAllocatedPointer.mpData, asAllocatedPointer.msFile.c_str(),asAllocatedPointer.mlLine);

		return asAllocatedPointer.mpData;
	}

	void* cMemoryManager::UpdatePointer(void* apOldData, const cAllocatedPointer& aNewAllocatedPointer)
	{
		DeletePointer(apOldData, aNewAllocatedPointer.msFile.c_str(), aNewAllocatedPointer.mlLine);
		return AddPointer(aNewAllocatedPointer);

	}

	bool cMemoryManager::DeletePointer(void* apData, const char* apFileString, int alLine)
	{
		bool bFound = false;
		tAllocatedPointermapIterator it = m_mapPointers.upper_bound(apData);
		it--;
		if (it != m_mapPointers.end())
		{
			char* apTest = (char*)it->second.mpData;
			size_t testSize = it->second.mlMemorySize;
			if (apData >= apTest && apData < apTest + testSize) bFound = true;
			
		}
		
		if (bFound == false)
		{
			Warning("Pointer %d in %s at %d does not exist!\n", apData, apFileString, alLine);
			return false;
		}

		mlTotalMemoryUsage -= it->second.mlMemorySize;

		m_mapPointers.erase(it);
		return true;
	}

	void cMemoryManager::MemoryLog()
	{
		Log("----------Memory Manager Report----------\n");
		Log("|\n");

			if (m_mapPointers.empty())
			{
				Log("| No memory leaks detected. Memory Left: %d\n", mlTotalMemoryUsage);
			}
			else
			{
				Log("| Memory leaks detected:\n");
				Log("|");

				Log("| address\t file");

				int lMax = 0;
				tAllocatedPointermapIterator it = m_mapPointers.begin();

				for (; it != m_mapPointers.end(); ++it)
				{
					cAllocatedPointer& ap = it->second;
					if ((int)ap.msFile.length() > lMax)
						lMax = (int)ap.msFile.length();
				}

				lMax += 5;

				for (int i = 0; i < lMax - 4; ++i) Log(" ");

				Log("line\t\t memory usage\t   \n");

				Log("|-----------------------------------------------------\n");

				it = m_mapPointers.begin();
				for (; it != m_mapPointers.end(); ++it)
				{
					cAllocatedPointer& ap = it->second;
					Log("| 0x%p\t %s ", ap.mpData, ap.msFile.c_str());
					for (int i = 0; i < lMax - (int)ap.msFile.length(); ++i) Log(" ");
					Log("%s", ap.msFile.c_str());
					Log("%d\t\t%d\t\n", ap.mlLine, ap.mlMemorySize);
				}
			}
			Log("|\n");
			Log("-----------------------------------------------------\n");
	}
}