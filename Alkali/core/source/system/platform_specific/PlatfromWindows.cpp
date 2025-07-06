#include "system/Platform.h"

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



	bool cPlatform::FileExists(const twString& asFileName)
	{
		FILE* pFile = _wfopen(asFileName.c_str(), L"rb");
		if (pFile == NULL) {
			return false;
		}
		fclose(pFile);

		return true;
	}

	


}

