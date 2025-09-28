#include "system/Platform.h"
#include "engine/LogWriter.h"

#define UNICODE

#include "windows.h"
#include "stdio.h"
#include "shlobj.h"
#include "io.h"
#include <time.h>
#include <sys/stat.h>
#include <direct.h>
#include <cstdarg>


namespace alk {

	bool cPlatform::CopyFileToBuffer(const twString& asFileName, void* apBuffer, unsigned long alSize)
	{
		FILE* pFile = OpenFile(asFileName, L"rb");
		if (pFile == NULL) return false;
		fread(apBuffer, sizeof(alSize), alSize, pFile);

		fclose(pFile);
		return true;
	}



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

	bool cPlatform::FileExists(const twString& asFile)
	{
		FILE* pFile = OpenFile(asFile, L"rb");
		if (pFile == NULL){
			return false;
		}
		return true;
	}

	twString cPlatform::GetFuleFilePath(const twString& asFile)
	{
		wchar_t sBuff[2048];
		int blah = GetFullPathNameW(asFile.c_str(), 2048, sBuff, NULL);
		return sBuff;
	}

	bool cPlatform::CreateFolder(const twString& asPath, const twString asFolderName)
	{
		twString sFullPath = cString::ReplaceW(asPath, L"/", L"\\");

		return CreateDirectory(sFullPath.c_str(), NULL) == TRUE;
	}



	bool cPlatform::DeleteFolder(const twString& asPath, bool abDeleteSubDirs, bool abDeleteFiles)
	{
		twString sTempDir = cString::ReplaceW(asPath, L"/", L"\\");
		Log("%ls\n", sTempDir.c_str());

		if (abDeleteFiles)
		{
			twStringList lstFiles;
			FindFilesInDirectory(lstFiles, sTempDir, L"*.*", true);
			for (twStringListIt it = lstFiles.begin(); it != lstFiles.end(); ++it)
			{
				Log("File: %ls\n", (*it).c_str());
				twString sFilePath = cString::SetFilePathW(*it, sTempDir);
				RemoveFile(sFilePath);
			}
		}

		if (abDeleteSubDirs)
		{
			twStringList lstFolders;
			FindFoldersInDirectory(lstFolders, sTempDir, false, true);
			for (twStringListIt it = lstFolders.begin(); it != lstFolders.end(); ++it)
			{
				Log("Subdir: %ls\n", (*it).c_str());
				twString sFolderPath = cString::SetFilePathW(*it, sTempDir);
				DeleteFolder(sFolderPath, abDeleteSubDirs, abDeleteFiles);
			}
		}

		
		if (RemoveDirectory(sTempDir.c_str()) != TRUE) 
		{
			wchar_t sBuff[2048];
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, sBuff, 2048, NULL);
			Error("Could not remove directory %s: %s\n", cString::To8BitChar(sTempDir).c_str(), cString::To8BitChar(sBuff).c_str());
			return false;
		}

		return false;
	}

	void cPlatform::ExecuteURL(const twString& asURL)
	{
		ShellExecute(NULL, L"open", asURL.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	bool cPlatform::RunProcess(const twString& asFilePath, const twString& asCommandLine)
	{
		twString sWinPath = cString::ReplaceW(asFilePath, L"/", L"\\");

		PROCESS_INFORMATION pi;
		STARTUPINFO si;

		ZeroMemory(&si, sizeof(si));

		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		si.wShowWindow = SW_SHOW;

		twString sCommandLine = asFilePath + L" " + asCommandLine;

		return CreateProcess(sWinPath.c_str(), (LPWSTR)sCommandLine.c_str(), NULL, NULL, false, 0, NULL, NULL, &si, &pi) == TRUE;
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
		if (lHandle == -1L) 
		{ 
			return; 
		}
		
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

	static bool GetFolderProperties(struct _wfinddata_t* pFileInfo, bool abAddUpDir, bool abIncludeHidden)
	{
		if ((pFileInfo->attrib & _A_SUBDIR) == 0) return false;
		if (abIncludeHidden == false && (pFileInfo->attrib & _A_HIDDEN)) return false;

		twString sName = pFileInfo->name;
		if (sName == L"..") return abAddUpDir;
		if (sName == L".") return false;
	}

	void cPlatform::FindFoldersInDirectory(twStringList& aLst, const twString& asPath, bool abAddUpDir, bool abIncludeHidden)
	{
		// setup the search path
		twString sWinPath = cString::ReplaceW(asPath, L"/", L"\\");

		wchar_t buf[1024];
		wchar_t sEnd = sWinPath[sWinPath.size() - 1];
		if (sEnd == L'\\' || sEnd == L'/')
			swprintf(buf, 1024, L"%s%s", sWinPath.c_str(), L"*.*");
		else 
		{
			swprintf(buf, 1024, L"%s\\%s", sWinPath.c_str(), L"*.*");
		}

		//Log("%ls", buf);
		intptr_t lHandle;
		struct _wfinddata_t FileInfo;
		lHandle = _wfindfirst(buf, &FileInfo);

		if (lHandle == -1L) return;
	
		if (GetFolderProperties(&FileInfo, abAddUpDir, abIncludeHidden)) aLst.push_back(FileInfo.name);
		while (_wfindnext(lHandle, &FileInfo) == 0)
		{
			if (GetFolderProperties(&FileInfo, abAddUpDir, abIncludeHidden)) 
			{
				aLst.push_back(FileInfo.name);
				//Log("Found folder: %ls\n", FileInfo.name);
			} 
		}

		_findclose(lHandle);
	}

	static cDate DateFromGMT(struct tm* Time)
	{
		cDate Date;
		Date.Seconds = Time->tm_sec;
		Date.Minutes = Time->tm_min;
		Date.Hours = Time->tm_hour;
		Date.Day = Time->tm_mday;
		Date.weeks = Time->tm_wday;
		Date.Month = Time->tm_mon;
		Date.Year = Time->tm_year + 1900;
		return Date;
	}

	cDate cPlatform::GetFileModificationDate(const twString& asFile)
	{
		struct tm* Time;
		struct _stat atrib;
		_wstat(asFile.c_str(), &atrib);

		Time = gmtime(&atrib.st_mtime);

		cDate Date = DateFromGMT(Time);
		return Date;
	}

	cDate cPlatform::GetLocalTime()
	{
		time_t lTime;
		time(&lTime);
		
		struct tm* sTime;
		sTime = localtime(&lTime);

		return DateFromGMT(sTime);
	}

	cDate cPlatform::GetFileCreationDate(const twString& asFile)
	{
		struct tm* Time;
		struct _stat atrib;
		_wstat(asFile.c_str(), &atrib);

		Time = gmtime(&atrib.st_ctime);

		cDate Date = DateFromGMT(Time);
		return Date;
	}



	unsigned long cPlatform::GetNumberOfDrives()
	{
		return _getdrives();
	}

	twString cPlatform::GetCurrentWorkingDirectory()
	{
		twString sDir = twString(_wgetcwd(NULL, 0));
		return sDir;
	}

	twString cPlatform::GetSpecialFolder(eSystemSpecialPath aeSystemSpecialPath)
	{
		twString sOutput = L"";

		int lType;
		switch (aeSystemSpecialPath)
		{
		case eSystemSpecialPath_ePersonalDirectory:
			lType = CSIDL_PERSONAL;
			break;
		case eSystemSpecialPath_eLocal:
			lType = CSIDL_LOCAL_APPDATA;
			break;
		default: return L"";
		}

		WCHAR sPath[2048];
		if (SUCCEEDED(SHGetFolderPath(NULL, lType | CSIDL_FLAG_CREATE, NULL, 0, sPath)))
		{
			sOutput = twString(sPath);
		}
		else 
		{ 
			return L"";
		}

		if (cString::GetLastCharW(sOutput) != L"/" &&
			cString::GetLastCharW(sOutput) != L"\\")
		{
			sOutput += L"\\";
		}
			return sOutput;
	}


	unsigned long long cPlatform::GetSysUpTime()
	{
		return GetTickCount64();
	}



	void cPlatform::CreateMessageBoxPlatform(eMessageBoxType aeMessageBoxType, const wchar_t* asCaption, const wchar_t* fmt, va_list aVaList)
	{
		UINT lType = MB_OK;

		wchar_t buff[2048];
		vswprintf(buff, 2048, fmt, aVaList);

		twString sMessage = L"";
		sMessage += buff;

		switch (aeMessageBoxType)
		{
		case eBoxTypeMessage:
			lType += MB_ICONINFORMATION;
			break;
		case eBoxTypeWarning:
			lType += MB_ICONWARNING;
			break;
		case eBoxTypeError:
			lType += MB_ICONERROR;
			break;
		default:
			break;
		}

		MessageBoxW(NULL, sMessage.c_str(), asCaption, lType);
	}

}

