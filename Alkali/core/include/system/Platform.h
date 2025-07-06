#ifndef ALK_PLATFORM_H
#define ALK_PLATFORM_H

#include "system/String.h"

namespace alk {

	class cPlatform
	{
	public:
		static bool CopyFileToBuffer(const twString& asFileName, void* apBuffer, unsigned long alSize);
		static void CopyToClipboard(const tString& asString);

		static int GetFileSize(const twString& asFile);
		static int GetFileSize(const FILE* &asFile);

		static FILE* OpenFile(const twString& asFileName, const twString& asMode);
		static void RemoveFile(const twString& asFile);

		static bool FileExists(const twString& asFileName);

		static bool CreateFolder(const twString& asPath, const twString asFolderName);
		static bool DeleteFolder(const twString& asPath, bool abDeleteSubDirs, bool abDeleteFiles);

		static void CreateURL(const twString& asURL);

		static unsigned int GetAppTime();

		static bool FindFilesInDirectory(const twString& asPath, const twString& asFileName);

		static bool CreateMessageBox();

		static void CreateThread();
		


	};


}
#endif