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
		cJSON* pObject = NULL;
		
		cJSON_ArrayForEach(pObject, pRoot)
		{
			// does the object have children?
			LoadJsonObject(pObject);
		}

		/*LoadJsonObject(pRoot);

		cJSON_Delete(pRoot);

		tMapValIterator it = mMapValues.begin();

		for (; it != mMapValues.end(); ++it)
		{
			Log("Name: '%s'\n", it->first.c_str());
			Log("Value: '%s'\n", it->second.c_str());
		}*/

		return true;
	}

	bool cJsonDocumentCJSON::LoadJsonObject(cJSON* apJSON)
	{
		cJSON* pJSON = apJSON;
		if (apJSON == NULL) return false;

		if (pJSON->type != cJSON_Object)
		{
			if (!cJSON_IsNull(pJSON))
			{
				tString sName = cString::toString(pJSON->string, "");
				tString sValue = ConvertToString(pJSON);

				int lRep = mMapValues.count(sName);
				if (true)//lRep <= 0)
				{
					mMapValues.insert(tMapValues::value_type(sName, sValue));
				}
				else
				Warning("Value '%s' already exists! skipping\n", sName.c_str());
			}
		}
		cJSON* pChild = NULL;
		cJSON_ArrayForEach(pChild, pJSON)
		{
			LoadJsonObject(pChild);
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