#ifndef ALK_PLATFORM_H
#define ALK_PLATFORM_H

#include "system/String.h"

namespace alk {
	class cPlatform
	{
	public:
		static bool CopyFileToBuffer(const twString& asFileName, void* apBuffer, unsigned long alSize);
		
		static bool CreateFolder(const twString& asPath, const twString asFolderName);
		static bool DeleteFolder(const twString& asFolder);
		static bool DeleteMultipleFolders(const twString& asPath, bool abDeleteSubDirs, bool abDeleteFiles);

		static void RenameFile(const twString& asFile, const twString& asName);
		static void RenameDir(const twString& asDir, const twString& asName);

		FILE* OpenFile(const twString& asFileName);

		static bool CreateMessageBox();
	};


}
#endif