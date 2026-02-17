#ifndef ALK_PLATFORM_H
#define ALK_PLATFORM_H

#include "system/String.h"
#include "system/SystemTypes.h"

#include <cstdarg>

#include "system/Date.h"

namespace alk {

	class cPlatform
	{
	public:
		static bool CopyFileToBuffer(const twString& asFileName, void* apBuffer, unsigned long alSize);
		static void CopyToClipboard(const tString& asString);
		static void PasteFromClipboard(tString& asString);

		static int GetFileSize(const twString& asFile);

		static FILE* OpenFile(const twString& asFileName, const twString& asMode);
		static void RemoveFile(const twString& asFile);
		static bool FileExists(const twString& asFile);
		static twString GetFullFilePath(const twString& asFile);

		static bool CreateFolder(const twString& asPath, const twString asFolderName);
		static bool DeleteFolder(const twString& asPath, bool abDeleteSubDirs, bool abDeleteFiles);

		static void ExecuteURL(const twString& asURL);
		static bool RunProcess(const twString& asFilePath, const twString& asCommandLine);

		static void FindFilesInDirectory(twStringList &aLst, const twString& asPath, const twString& asFilter, bool abIncludeHidden);
		static void FindFoldersInDirectory(twStringList& aLst, const twString& asPath, bool abAddUpDir, bool abIncludeHidden);
		
		static cDate GetFileCreationDate(const twString& asFile);
		static cDate GetFileModificationDate(const twString& asFile);
		static cDate GetLocalTime();

		static twString GetProcessorModel();
		static twString GetProcessorArchitecture();
		static int GetProcessorCores();
		static int GetProcessorLogicalProcessors();

		static size_t GetAvailableRam();
		static size_t GetTotalRam();
		static unsigned long GetNumberOfDrives();
		static twString GetCurrentWorkingDirectory();
		static twString GetSpecialFolder(eSystemSpecialPath aeSystemSpecialPath);

		static unsigned long long GetAppTime();
		static unsigned long long GetSysUpTime();

		static void Sleep(int alMS);

		static void CreateMessageBox(eMessageBoxType aeMessageBoxType, const wchar_t* asCaption, const wchar_t* fmt, ...);

		static void CreateThread();
		
		static twString GetProfileName();

	private:
		static void CreateMessageBoxPlatform(eMessageBoxType aeMessageBoxType, const wchar_t* asCaption, const wchar_t* fmt, va_list aVaList);
	};
}
#endif