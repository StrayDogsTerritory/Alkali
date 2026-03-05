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

	iJsonDocument::~iJsonDocument() 
	{
		
	}

	bool  iJsonDocument::LoadDocument(const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"rb");

		if (pFile == NULL)
		{
			Error("File '%s' could not be opened!\n", cString::To8BitChar(asFile));
			return false;
		} 
		///////////////
		// read file in as a C string
		fseek(pFile, 0, SEEK_END);
		size_t lSize = ftell(pFile);
		rewind(pFile);

		char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize +1);
		fread(pBuffer, sizeof(char), lSize, pFile);
		pBuffer[lSize] = 0;
		fclose(pFile);
		// parse the document
		bool bRet = Parse(pBuffer);

		alkFree(pBuffer);
		
		return bRet;
	}
	
	tString iJsonDocument::GetValueString(const tString& asName, const char* asFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if(it == mMapValues.end()) return asFallback;

		return cString::toString(it->second.c_str(), asFallback);
	}

	int iJsonDocument::GetValueInt(const tString& asName, int alFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return alFallback;

		return cString::ToInt(it->second.c_str(),alFallback);
	}

	float iJsonDocument::GetValueFloat(const tString& asName, float afFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return afFallback;

		return cString::ToFloat(it->second.c_str(), afFallback);
	}

	bool iJsonDocument::GetValueBool(const tString& asName, bool abFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return NULL;

		if (it->second.c_str() == NULL) return NULL;

		return cString::ToBool(it->second.c_str(), abFallback);
	}


}

