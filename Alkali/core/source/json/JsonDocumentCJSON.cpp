#include "json/JsonDocumentCJSON.h"

#include "engine/LogWriter.h"

namespace alk {

	cJsonDocumentCJSON::cJsonDocumentCJSON(const tString& asName)
	: iJsonDocument(asName)
	{

	}

	cJsonDocumentCJSON::~cJsonDocumentCJSON()
	{

	}

	bool cJsonDocumentCJSON::Parse(char* apString)
	{
		cJSON* pRoot = cJSON_Parse(apString);

		if (pRoot == NULL) return false;

		cJSON* pObject = pRoot->child;
	
		LoadJsonObject(pObject, this);
		
		cJSON_Delete(pRoot);

		return true;
	}

	char* cJsonDocumentCJSON::Save()
	{
		cJSON* pRoot = cJSON_CreateObject();

		SaveJsonObject(pRoot, this);

		char* sRet = cJSON_Print(pRoot);
		cJSON_Delete(pRoot);

		return sRet;

	}

	bool cJsonDocumentCJSON::SaveJsonObject(cJSON* apJSON, cJsonObject* apObject)
	{
		std::list<cJsonObject*>::iterator it = apObject->mLstChildren.begin();
		for (; it != apObject->mLstChildren.end(); ++it)
		{
			cJSON* pChild = cJSON_CreateObject();

			cJsonObject* pChildObject = (*it);

			tMapValues Map = pChildObject->mMapValues;

			for (tMapValIterator it = Map.begin(); it != Map.end(); ++it)
			{
				cJSON_AddStringToObject(pChild, it->first.c_str(), it->second.c_str());
			}

			cJSON_AddItemToObject(apJSON, pChildObject->msName.c_str(), pChild);

			// run this recursivly for each child
			SaveJsonObject(pChild, pChildObject);
		}

		return true;
	}

	bool cJsonDocumentCJSON::LoadJsonObject(cJSON* apJSON, cJsonObject* apObject)
	{

		while (apJSON != NULL)
		{
			if (apJSON->type == cJSON_Array)
			{
				Warning("Object '%s' could not be loaded! JSON arrays are not supported!\n", apJSON->string); 
				return false;
			}

			if (apJSON->type != cJSON_Object)
			{
				apObject->mMapValues.insert(tMapValues::value_type(cString::toString(apJSON->string, ""), ConvertToString(apJSON)));
			}

			else
			{
				cJsonObject* pSubObject = apObject->CreateChildObject(cString::toString(apJSON->string, ""));

				cJSON* pJSONChild = apJSON->child;
				while (pJSONChild != NULL)
				{
					LoadJsonObject(pJSONChild, pSubObject);

					pJSONChild = pJSONChild->child;
				}
			}

			apJSON = apJSON->next;
		}

		return true;
	}

	

	tString cJsonDocumentCJSON::ConvertToString(cJSON* apJSON)
	{
		if (apJSON->type == cJSON_String) return cString::toString(apJSON->valuestring, "");
		else if (apJSON->type == cJSON_Number) return cString::ToStringFloat(GetNumber(apJSON), "0.0f");

		else return apJSON->type == cJSON_True ? "true" : "false";
	}



	float inline cJsonDocumentCJSON::GetNumber(cJSON* apJSON)
	{
		if (apJSON->valueint != NULL) return (float)apJSON->valueint;
		else if (apJSON->valuedouble != NULL) return (float)apJSON->valuedouble;

		return NULL;
	}




	const char* cJsonDocumentCJSON::GetErrorMsg()
	{
		return cJSON_GetErrorPtr();
	}
}