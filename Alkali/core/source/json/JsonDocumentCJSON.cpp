#include "json/JsonDocumentCJSON.h"

#include "engine/LogWriter.h"

namespace alk {

	cJsonDocumentCJSON::cJsonDocumentCJSON()
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

			Log("Name: %s\n", pObject->string);

			if (pObject->type == cJSON_Object)
			{
				cJSON* pSubObject = NULL;
				cJSON_ArrayForEach(pSubObject, pObject)
				{
					if (pSubObject->type != cJSON_String) Log("Name: %s, no value, not string\n", pSubObject->string);
					else { Log("Name: %s, Value: %s\n", pSubObject->string, pSubObject->valuestring); }
					//	cJSON_Delete(pSubObject);
				}
			}
	}
}