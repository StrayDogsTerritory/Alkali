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

	void cJsonDocumentCJSON::Parse(char* apString)
	{
		cJSON* pRoot = cJSON_Parse(apString);
		cJSON* pObject = NULL;

		cJSON_ArrayForEach(pObject, pRoot) {

			//Log("Object Name: %s\n", pObject->string);

			if (pObject->type == cJSON_Object)
			{
				cJSON* pSubObject = NULL;
				cJSON_ArrayForEach(pSubObject, pObject)
				{
					//Log("Name: %s, Value: %s\n", pSubObject->string, ConvertToString(pSubObject).c_str());
					mMapValues.insert(std::map<tString, tString>::value_type(pSubObject->string, ConvertToString(pSubObject)));
				}
			}
		}

		cJSON_Delete(pObject);
		cJSON_Delete(pRoot);
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
}