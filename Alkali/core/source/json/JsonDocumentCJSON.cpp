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
	
		while (pObject != NULL)
		{
			cJsonObject* pElement = alkNew(cJsonObject, (cString::toString(pObject->string, "")));
			AddChild(pElement);
			
			cJSON* pChild = pObject->child;
			if (pChild)LoadJsonObject(pChild, pElement);
			

			pObject = pObject->next;
		}
		
		cJSON_Delete(pRoot);

		return true;
	}

	bool cJsonDocumentCJSON::LoadJsonObject(cJSON* apJSON, cJsonObject* apObject)
	{
		//apJSON = apJSON->child;

		while (apJSON != NULL)
		{
			cJsonObject* pLoopObject = apObject;

			if (apJSON->type == cJSON_Object)
			{
				pLoopObject = alkNew(cJsonObject, (cString::toString(apJSON->string, "")));
				apObject->AddChild(pLoopObject);
			}
				pLoopObject->mMapValues.insert(tMapValues::value_type(cString::toString(apJSON->string, ""), ConvertToString(apJSON)));

			while (apJSON->child != NULL)
			{
				apJSON = apJSON->child;

				cJsonObject* pChild = alkNew(cJsonObject, (cString::toString(apJSON->string, "")));
				pLoopObject->AddChild(pChild);

				pChild->mMapValues.insert(tMapValues::value_type(cString::toString(apJSON->string, ""), ConvertToString(apJSON)));

				LoadJsonObject(apJSON, pChild);
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



	float cJsonDocumentCJSON::GetNumber(cJSON* apJSON)
	{
		if (apJSON->valueint != NULL) return (float)apJSON->valueint;
		else if (apJSON->valuedouble != NULL) return (float)apJSON->valuedouble;

		return NULL;
	}




	char* cJsonDocumentCJSON::GetErrorMsg()
	{
		const char* sRet = cJSON_GetErrorPtr();

		return (char*)sRet;
	}
}