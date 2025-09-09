#ifndef ALK_FILESEARCHER_H
#define ALK_FILESEARCHER_H

#include "system/String.h"

#include <map>

namespace alk
{

	class cFileSearcherEntry
	{
	public:
		cFileSearcherEntry(const twString& asName);
		
		twString msPath;
	};

	typedef std::multimap<tString, cFileSearcherEntry> mFileSearcherMap;
	typedef mFileSearcherMap::iterator mFileSearcherMapIt;

	class cFileSearcher
	{
	public:
		cFileSearcher();
		~cFileSearcher();

		void AddDir(const twString& asFilePath, const tString& asFilter, const bool& abAddSubDirs);
		void ClearDirs();
		const twString GetPath(const tString& asFilePath);
		
	private:
		mFileSearcherMap mEntries;

	};


}

#endif