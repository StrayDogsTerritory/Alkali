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

		static bool CreateFolder(const twString& asPath, const twString asFolderName);
		static bool DeleteFolder(const twString& asPath, bool abDeleteSubDirs, bool abDeleteFiles);

		static void ExecuteURL(const twString& asURL);


		static void FindFilesInDirectory(twStringList &aLst, const twString& asPath, const twString& asFilter, bool abIncludeHidden);

		static bool CreateMessageBox();

		static void CreateThread();
		


	};


}
#endif