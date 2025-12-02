#include "Alkali.h"

using namespace alk;

int AlkaliMain(const tString& asCommandLine)
{
	FILE* pFile = cPlatform::OpenFile(L"X:\\Alkali\\Toronto\\redist\\Toronto.exe", L"rb");

	if (pFile == NULL)
	{
		//fclose(pFile);
		Log("Couldn't find Toronto.exe!\n");
		exit(1);
		return 1;
	}
	fseek(pFile, 0, SEEK_END);
	size_t lSize = ftell(pFile);
	rewind(pFile);

	char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize + 1);
	fread(pBuffer, sizeof(char), lSize, pFile);
	pBuffer[lSize] = 0;
	fclose(pFile);

	int lHash = cString::Hash(tString(pBuffer));
	Log("Hash: '%u'\n", lHash);
	alkFree(pBuffer);
	return 0;
}