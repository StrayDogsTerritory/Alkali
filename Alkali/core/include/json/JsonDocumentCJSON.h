#ifndef ALK_JSONDOCUMENTCJSON_H
#define ALK_JSONDOCUMENTCJSON_H

#include "json/JsonDocument.h"

#include <json/cJson/cJSON.h>

namespace alk {

	class cJsonDocumentCJSON : public iJsonDocument
	{
	public:
		cJsonDocumentCJSON(const tString& asName);
		~cJsonDocumentCJSON();

		bool Parse(char* apString);

		bool LoadJsonObject(cJSON* apJSON, cJsonObject* apObject);

		tString ConvertToString(cJSON* apJSON);

		float GetNumber(cJSON* apJSON);
		

		char* GetErrorMsg();
	};

}
#endif
