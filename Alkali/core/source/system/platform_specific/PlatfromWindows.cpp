#include "system/Platform.h"

#include "windows.h"
#include "stdio.h"
#include "shlobj.h"
#include "io.h"


namespace alk {

	FILE* cPlatform::OpenFile(const twString& asFileName, const twString &asMode)
	{
		return _wfopen(asFileName.c_str(), asMode.c_str());
	}

}

