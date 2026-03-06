#include "json/JsonDocumentCJSON.h"

#include "engine/LogWriter.h"

namespace alk {

	cJsonDocumentCJSON::cJsonDocumentCJSON()
	: iJsonDocument()
	{

	}

	cJsonDocumentCJSON::~cJsonDocumentCJSON()
	{

	}

	bool cJsonDocumentCJSON::Parse(char* apString)
	{
		cJSON* pRoot = cJSON_Parse(apString);
		cJSON* pSubRoot = NULL;
		if (pRoot == NULL) return false;

		tString sName = cString::toString(pRoot->valuestring, "");
		tString sValue = ConvertToString(pRoot);

		mMapValues.insert(tMapValues::value_type(sName, sValue));

		cJSON_ArrayForEach(pSubRoot, pRoot)
		{
			Parse
		}
		//cJSON_ArrayForEach(pObject, pRoot) {

		//	//Log("Object Name: %s\n", pObject->string);
		//	mMapValues.insert(tMapValues::value_type(pObject->string, ConvertToString(pObject)));
		//	if (pObject->type == cJSON_Object)
		//	{
		//		cJSON* pSubObject = NULL;
		//		cJSON_ArrayForEach(pSubObject, pObject)
		//		{
		//			//Log("Name: %s, Value: %s\n", pSubObject->string, ConvertToString(pSubObject).c_str());
		//			
		//		}
		//	}
	//}

		cJSON_Delete(pRoot);

		return true;
	}

	tString cJsonDocumentCJSON::ConvertToString(cJSON* apJSON)
	{
		if (apJSON->type == cJSON_String) return apJSON->valuestring;
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