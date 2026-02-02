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
		int lFileSize = ftell(pFile);
		rewind(pFile);

		return lFileSize;
	}



	FILE* cPlatform::OpenFile(const twString& asFileName, const twString &asMode)
	{
		return _wfopen(asFileName.c_str(), asMode.c_str());
	}

	


}

