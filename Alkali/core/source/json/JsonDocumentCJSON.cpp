#include "json/JsonDocumentCJSON.h"

#include "engine/LogWriter.h"

namespace alk {

	cJsonDocumentCJSON::cJsonDocumentCJSON()
	: iJsonDocument("")
	{

	}

	cJsonDocumentCJSON::~cJsonDocumentCJSON()
	{

	}

	bool cJsonDocumentCJSON::Parse(char* apString)
	{
		cJSON* pRoot = cJSON_Parse(apString);
		cJSON* pObject = pRoot->child;

		cJsonObject* pRootObject = alkNew(cJsonObject, ("document_root"));
	
		cJsonObject* pFirstElement = alkNew(cJsonObject, (cString::toString(pObject->string, "")));
		pRootObject->AddChild(pFirstElement);

		while (pObject->next != NULL)
		{
			pObject = pObject->next;
			cJsonObject

			while (pObject->child != NULL)
			{

			}
			
		}
		


		return false;
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