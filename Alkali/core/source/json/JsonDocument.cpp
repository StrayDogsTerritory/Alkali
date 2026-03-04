#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/String.h"
#include "system/Platform.h"

#include "engine/LogWriter.h"

#include "json/cJson/cJSON.h"

namespace alk {

	iJsonDocument::iJsonDocument()
	{

	}

	iJsonDocument::~iJsonDocument() {}

	void iJsonDocument::LoadDocument(const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"rb");

		if (pFile == NULL)
		{
			Error("File '%s' could not be opened!\n", cString::To8BitChar(asFile));
			return;
		}
		///////////////
		// read file in as a C string
		fseek(pFile, 0, SEEK_END);
		size_t lSize = ftell(pFile);
		rewind(pFile);

		char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize + 1);
		fread(pBuffer, sizeof(char), lSize, pFile);
		pBuffer[lSize] = 0;
		fclose(pFile);
		// parse the document
		Parse(pBuffer);
		alkFree(pBuffer);
		
	}
	

}

