#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/String.h"
#include "system/Platform.h"

#include "engine/LogWriter.h"

#include "json/cJson/cJSON.h"

namespace alk {


	tString cJsonObject::GetValueString(const tString& asName, const char* asFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return asFallback;

		return cString::toString(it->second.c_str(), asFallback);
	}

	int cJsonObject::GetValueInt(const tString& asName, int alFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return alFallback;

		return cString::ToInt(it->second.c_str(), alFallback);
	}

	float cJsonObject::GetValueFloat(const tString& asName, float afFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return afFallback;

		return cString::ToFloat(it->second.c_str(), afFallback);
	}

	bool cJsonObject::GetValueBool(const tString& asName, bool abFallback)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return NULL;

		return cString::ToBool(it->second.c_str(), abFallback);
	}



	iJsonDocument::iJsonDocument(const tString& asName)
		: cJsonObject(asName)
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
		
		tMapValues::iterator it = mMapValues.begin();
		for (; it != mMapValues.end(); ++it)
		{
			Debug("Name: '%s' Value: '%s'\n", it->first.c_str(), it->second.c_str());
		}

		return bRet;
	}
	
	


}

