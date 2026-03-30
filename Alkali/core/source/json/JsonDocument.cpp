#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/Platform.h"
#include "system/String.h"

#include "engine/LogWriter.h"

#include "json/cJson/cJSON.h"

namespace alk {


	cJsonObject::~cJsonObject()
	{
		DeleteAll(mLstChildren);
	}


	cJsonObject* cJsonObject::GetChildObject(const tString& asName)
	{
		std::list<cJsonObject*>::iterator it = mLstChildren.begin();
		for (; it != mLstChildren.end(); ++it)
		{
			cJsonObject* pObject = (*it);
			cJsonObject* pChild = NULL;

			if (pObject->msName == asName)
				return pObject;

			// if not found, search the children recursively
			pChild = pObject->GetChildObject(asName);
			if (pChild != NULL) return pChild;
		}

		return NULL;
	}

	cJsonObject* cJsonObject::CreateChildObject(const tString& asName)
	{
		cJsonObject* pObject = alkNew(cJsonObject, (asName));
		AddChild(pObject);

		return pObject;
	}

	void cJsonObject::DestroyChildObject(const tString& asName)
	{
		if (asName == "") return;

		for (std::list<cJsonObject*>::iterator it = mLstChildren.begin(); it != mLstChildren.end(); ++it)
		{
			cJsonObject* pObject = (*it);
			if (pObject->msName == asName)
			{
				alkDelete(pObject);
			}
		}
	}



	void cJsonObject::AddChild(cJsonObject* apObject)
	{
		if (apObject == NULL) return;

		apObject->mpParent = this;

		mLstChildren.push_back(apObject);
	}



	void cJsonObject::SetValue(const tString& asName, const tString asVal)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return;

		it->second = asVal;
	}



	void cJsonObject::SetValueString(const tString& asName, const tString& asValue, const tString& asFallBack)
	{
		SetValue(asName, asValue);
	}



	void cJsonObject::SetValueInt(const tString& asName, int alX, const tString& asFallBack)
	{
		SetValue(asName,cString::ToStringInt(alX, asFallBack));
	}



	void cJsonObject::SetValueFloat(const tString& asName, float afX, const tString& asFallBack)
	{
		SetValue(asName, cString::ToStringFloat(afX, asFallBack));
	}



	void cJsonObject::SetValueBool(const tString& asName, bool abX, const tString& asFallBack)
	{
		SetValue(asName, cString::ToStringBool(abX, asFallBack));
	}



	void cJsonObject::SetValueVector2l(const tString& asName, tVector2l avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector2l(avVec, asFallback));
	}



	void cJsonObject::SetValueVector2f(const tString& asName, tVector2f avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector2f(avVec, asFallback));
	}



	void cJsonObject::SetValueVector3l(const tString& asName, tVector3l avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector3l(avVec, asFallback));
	}



	void cJsonObject::SetValueVector3f(const tString& asName, tVector3f avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector3f(avVec, asFallback));
	}



	tString cJsonObject::GetValue(const tString& asName)
	{
		tMapValIterator it = mMapValues.find(asName);
		if (it == mMapValues.end()) return "";

		return it->second;
	}



	tString cJsonObject::GetValueString(const tString& asName, const char* asFallback)
	{
		return cString::toString(GetValue(asName).c_str(), asFallback);
	}



	int cJsonObject::GetValueInt(const tString& asName, int alFallback)
	{
		return cString::ToInt(GetValue(asName).c_str(), alFallback);
	}



	float cJsonObject::GetValueFloat(const tString& asName, float afFallback)
	{
		return cString::ToFloat(GetValue(asName).c_str(), afFallback);
	}



	bool cJsonObject::GetValueBool(const tString& asName, bool abFallback)
	{
		return cString::ToBool(GetValue(asName).c_str(), abFallback);
	}



	tVector2l cJsonObject::GetValueVector2l(const tString& asName, tVector2l avFallback)
	{
		return cString::ToVector2l(GetValue(asName).c_str(), avFallback);
	}



	tVector2f cJsonObject::GetValueVector2f(const tString& asName, tVector2f avFallback)
	{
		return cString::ToVector2f(GetValue(asName).c_str(), avFallback);
	}



	tVector3l cJsonObject::GetValueVector3l(const tString& asName, tVector3l avFallback)
	{
		return cString::ToVector3l(GetValue(asName).c_str(), avFallback);
	}



	tVector3f cJsonObject::GetValueVector3f(const tString& asName, tVector3f avFallback)
	{
		return cString::ToVector3f(GetValue(asName).c_str(), avFallback);
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

		if (bRet == false)
		{
			Error("Json document '%s' could not be loaded! Reason: '%s'\n", msName.c_str(), GetErrorMsg());
			return false;
		}

		return true;
	}

	bool iJsonDocument::SaveDocument(const twString& asFilePath)
	{
		FILE* pFile = cPlatform::OpenFile(asFilePath, L"w");

		if (pFile == NULL)
		{
			Error("Could not open file '%s' for saving!\n", cString::To8BitChar(asFilePath).c_str());
			return false;
		}

		char* sFile = Save();

		if (sFile == NULL)
		{
			Error("Could not save file '%s'\n", cString::To8BitChar(asFilePath).c_str());
			return false;
		}

		fprintf(pFile, "%s", sFile);
	}
	
	


}

