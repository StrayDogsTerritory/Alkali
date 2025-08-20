#include "system/Platform.h"
#include "engine/LogWriter.h"

#define UNICODE

#include "windows.h"
#include "stdio.h"
#include "shlobj.h"
#include "io.h"


namespace alk {

	int GetFileSize(const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"rb");

		fseek(pFile, 0, SEEK_END);
		size_t lFileSize = ftell(pFile);
		rewind(pFile);

		return (int)lFileSize;
	}



	FILE* cPlatform::OpenFile(const twString& asFileName, const twString &asMode)
	{
		return _wfopen(asFileName.c_str(), asMode.c_str());
	}

	void cPlatform::RemoveFile(const twString& asFile)
	{
		 _wremove(asFile.c_str());
	}

	bool cPlatform::CreateFolder(const twString& asPath, const twString asFolderName)
	{
		twString sFullPath = cString::ReplaceW(asPath, L"/", L"\\");

		return CreateDirectory(sFullPath.c_str(), NULL) == TRUE;
	}

	void cPlatform::ExecuteURL(const twString& asURL)
	{
		ShellExecute(NULL, L"open", asURL.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}


		
	void cPlatform::FindFilesInDirectory(twStringList &aLst, const twString& asPath, const twString& asFilter, bool abIncludeHidden)
	{
		// setup the search path
		twString sWinPath = cString::ReplaceW(asPath, L"/", L"\\");
		// get filter properties
		int sAsteriskLastPos = cString::FindLastOfCharW(asFilter, L"*");
		twString sFilterExt = cString::ToLowerCaseW(cString::SubStringW(asFilter, sAsteriskLastPos + 2));
		bool bHasFilter = (sFilterExt != L"");

		wchar_t buf[1024];
		wchar_t sEnd = sWinPath[sWinPath.size() - 1];

		if (sEnd == L'\\'|| sEnd == L'/')
			swprintf(buf, 1024, L"%s%s", sWinPath.c_str(), asFilter.c_str());
		else
			swprintf(buf, 1024, L"%s\\%s", sWinPath.c_str(), asFilter.c_str());

		intptr_t lHandle;
		struct _wfinddata_t FileInfo;

		lHandle = _wfindfirst(buf, &FileInfo);
		if (lHandle == -1) return ;
		
		if ((FileInfo.attrib & _A_SUBDIR) == 0 && (abIncludeHidden || (FileInfo.attrib & _A_HIDDEN)==0)) 
		{
			if (bHasFilter)
			{
				if (cString::ToLowerCaseW(cString::FileExtensionW(FileInfo.name)) == sFilterExt) aLst.push_back(FileInfo.name);
			}
			aLst.push_back(FileInfo.name);
			
		}

		while(_wfindnext(lHandle, &FileInfo) == 0)
		{
			if((FileInfo.attrib & _A_SUBDIR) == 0 && (abIncludeHidden || (FileInfo.attrib & _A_HIDDEN)==0)) 
			{
				if (bHasFilter)
				{
					if (cString::ToLowerCaseW(cString::FileExtensionW(FileInfo.name)) == sFilterExt) aLst.push_back(FileInfo.name);
				}
				aLst.push_back(FileInfo.name);
			}
		}
		_findclose(lHandle);
	}

	


}

