#include "resources/FileSearcher.h"
#include "system/Platform.h"

#include "engine/LogWriter.h"
namespace alk {

	cFileSearcherEntry::cFileSearcherEntry(const twString& asPath)
	{
		msPath = asPath;
	}


	cFileSearcher::cFileSearcher()
	{

	}

	cFileSearcher::~cFileSearcher()
	{
		
	}

	void cFileSearcher::ClearDirs()
	{
		mEntries.clear();
	}

	void cFileSearcher::AddDir(const twString& asFilePath, const tString& asFilter, const bool& abAddSubDirs)
	{
		//Log("started\n");
		twString sPath = cString::ReplaceW(asFilePath, L"\\", L"/");
		twStringList lstFiles;
		cPlatform::FindFilesInDirectory(lstFiles, sPath, cString::ToWideChar(asFilter), true);
		for (twStringListIt it = lstFiles.begin(); it != lstFiles.end(); it++)
		{
			twString sFileName = *it;
			tString sNameLow = cString::ToLowerCase(cString::To8BitChar(sPath));
			twString sFilePath = cString::ReplaceW(cPlatform::GetFuleFilePath(cString::SetFilePathW(sFileName, sPath)), L"\\", L"/");

			mFileSearcherMapIt Pathit = mEntries.find(sNameLow);
			if (Pathit != mEntries.end() && Pathit->second.msPath == sFilePath)
			{
				continue;
			}
			mEntries.insert(mFileSearcherMap::value_type(sNameLow, cFileSearcherEntry(sFilePath) ));
			size_t lDebugCount = mEntries.size();
			Log("Container size: %d\n Added file: %s at %ls\n", lDebugCount, sNameLow.c_str(), sFilePath.c_str());
		}

		if (abAddSubDirs)
		{
			twStringList lstFolders;
			cPlatform::FindFoldersInDirectory(lstFolders, sPath, false, true);
			for (twStringListIt it = lstFolders.begin(); it != lstFolders.end(); ++it)
			{
				twString sFolderPath = cString::SetFilePathW(*it, sPath);
				AddDir(sFolderPath, asFilter, abAddSubDirs);
			}
		}
	}

	const twString cFileSearcher::GetPath(const tString& asFilePath)
	{
		tString sFileName = cString::FileName(asFilePath);
		tString sNameLow = cString::ToLowerCase(sFileName);

		mFileSearcherMapIt it = mEntries.find(sFileName);
		if (it != mEntries.end())
		{
			Log("  MEMEMEME ", it->second);
			return it->second.msPath;
		}
		return L"";
	}
}